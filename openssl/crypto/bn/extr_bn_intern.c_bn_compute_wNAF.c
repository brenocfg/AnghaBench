#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int* d; scalar_t__ top; } ;
typedef  TYPE_1__ BIGNUM ;

/* Variables and functions */
 int /*<<< orphan*/  BN_F_BN_COMPUTE_WNAF ; 
 int BN_is_bit_set (TYPE_1__ const*,size_t) ; 
 scalar_t__ BN_is_negative (TYPE_1__ const*) ; 
 scalar_t__ BN_is_zero (TYPE_1__ const*) ; 
 size_t BN_num_bits (TYPE_1__ const*) ; 
 int /*<<< orphan*/  BNerr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ERR_R_INTERNAL_ERROR ; 
 int /*<<< orphan*/  ERR_R_MALLOC_FAILURE ; 
 int /*<<< orphan*/  OPENSSL_free (char*) ; 
 char* OPENSSL_malloc (size_t) ; 

signed char *bn_compute_wNAF(const BIGNUM *scalar, int w, size_t *ret_len)
{
    int window_val;
    signed char *r = NULL;
    int sign = 1;
    int bit, next_bit, mask;
    size_t len = 0, j;

    if (BN_is_zero(scalar)) {
        r = OPENSSL_malloc(1);
        if (r == NULL) {
            BNerr(BN_F_BN_COMPUTE_WNAF, ERR_R_MALLOC_FAILURE);
            goto err;
        }
        r[0] = 0;
        *ret_len = 1;
        return r;
    }

    if (w <= 0 || w > 7) {      /* 'signed char' can represent integers with
                                 * absolute values less than 2^7 */
        BNerr(BN_F_BN_COMPUTE_WNAF, ERR_R_INTERNAL_ERROR);
        goto err;
    }
    bit = 1 << w;               /* at most 128 */
    next_bit = bit << 1;        /* at most 256 */
    mask = next_bit - 1;        /* at most 255 */

    if (BN_is_negative(scalar)) {
        sign = -1;
    }

    if (scalar->d == NULL || scalar->top == 0) {
        BNerr(BN_F_BN_COMPUTE_WNAF, ERR_R_INTERNAL_ERROR);
        goto err;
    }

    len = BN_num_bits(scalar);
    r = OPENSSL_malloc(len + 1); /*
                                  * Modified wNAF may be one digit longer than binary representation
                                  * (*ret_len will be set to the actual length, i.e. at most
                                  * BN_num_bits(scalar) + 1)
                                  */
    if (r == NULL) {
        BNerr(BN_F_BN_COMPUTE_WNAF, ERR_R_MALLOC_FAILURE);
        goto err;
    }
    window_val = scalar->d[0] & mask;
    j = 0;
    while ((window_val != 0) || (j + w + 1 < len)) { /* if j+w+1 >= len,
                                                      * window_val will not
                                                      * increase */
        int digit = 0;

        /* 0 <= window_val <= 2^(w+1) */

        if (window_val & 1) {
            /* 0 < window_val < 2^(w+1) */

            if (window_val & bit) {
                digit = window_val - next_bit; /* -2^w < digit < 0 */

#if 1                           /* modified wNAF */
                if (j + w + 1 >= len) {
                    /*
                     * Special case for generating modified wNAFs:
                     * no new bits will be added into window_val,
                     * so using a positive digit here will decrease
                     * the total length of the representation
                     */

                    digit = window_val & (mask >> 1); /* 0 < digit < 2^w */
                }
#endif
            } else {
                digit = window_val; /* 0 < digit < 2^w */
            }

            if (digit <= -bit || digit >= bit || !(digit & 1)) {
                BNerr(BN_F_BN_COMPUTE_WNAF, ERR_R_INTERNAL_ERROR);
                goto err;
            }

            window_val -= digit;

            /*
             * now window_val is 0 or 2^(w+1) in standard wNAF generation;
             * for modified window NAFs, it may also be 2^w
             */
            if (window_val != 0 && window_val != next_bit
                && window_val != bit) {
                BNerr(BN_F_BN_COMPUTE_WNAF, ERR_R_INTERNAL_ERROR);
                goto err;
            }
        }

        r[j++] = sign * digit;

        window_val >>= 1;
        window_val += bit * BN_is_bit_set(scalar, j + w);

        if (window_val > next_bit) {
            BNerr(BN_F_BN_COMPUTE_WNAF, ERR_R_INTERNAL_ERROR);
            goto err;
        }
    }

    if (j > len + 1) {
        BNerr(BN_F_BN_COMPUTE_WNAF, ERR_R_INTERNAL_ERROR);
        goto err;
    }
    *ret_len = j;
    return r;

 err:
    OPENSSL_free(r);
    return NULL;
}