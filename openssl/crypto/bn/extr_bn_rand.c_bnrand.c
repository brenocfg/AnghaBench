#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  OPENSSL_CTX ;
typedef  int /*<<< orphan*/  BN_CTX ;
typedef  scalar_t__ BNRAND_FLAG ;
typedef  int /*<<< orphan*/  BIGNUM ;

/* Variables and functions */
 int /*<<< orphan*/  BN_F_BNRAND ; 
 int BN_RAND_BOTTOM_ANY ; 
 int BN_RAND_TOP_ANY ; 
 int /*<<< orphan*/  BN_R_BITS_TOO_SMALL ; 
 int /*<<< orphan*/  BN_bin2bn (unsigned char*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  BN_zero (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  BNerr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ERR_R_MALLOC_FAILURE ; 
 scalar_t__ NORMAL ; 
 int /*<<< orphan*/  OPENSSL_clear_free (unsigned char*,int) ; 
 unsigned char* OPENSSL_malloc (int) ; 
 scalar_t__ TESTING ; 
 int /*<<< orphan*/  bn_check_top (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * bn_get_lib_ctx (int /*<<< orphan*/ *) ; 
 scalar_t__ rand_bytes_ex (int /*<<< orphan*/ *,unsigned char*,int) ; 
 scalar_t__ rand_priv_bytes_ex (int /*<<< orphan*/ *,unsigned char*,int) ; 

__attribute__((used)) static int bnrand(BNRAND_FLAG flag, BIGNUM *rnd, int bits, int top, int bottom,
                  BN_CTX *ctx)
{
    unsigned char *buf = NULL;
    int b, ret = 0, bit, bytes, mask;
    OPENSSL_CTX *libctx = bn_get_lib_ctx(ctx);

    if (bits == 0) {
        if (top != BN_RAND_TOP_ANY || bottom != BN_RAND_BOTTOM_ANY)
            goto toosmall;
        BN_zero(rnd);
        return 1;
    }
    if (bits < 0 || (bits == 1 && top > 0))
        goto toosmall;

    bytes = (bits + 7) / 8;
    bit = (bits - 1) % 8;
    mask = 0xff << (bit + 1);

    buf = OPENSSL_malloc(bytes);
    if (buf == NULL) {
        BNerr(BN_F_BNRAND, ERR_R_MALLOC_FAILURE);
        goto err;
    }

    /* make a random number and set the top and bottom bits */
    b = flag == NORMAL ? rand_bytes_ex(libctx, buf, bytes)
                       : rand_priv_bytes_ex(libctx, buf, bytes);
    if (b <= 0)
        goto err;

    if (flag == TESTING) {
        /*
         * generate patterns that are more likely to trigger BN library bugs
         */
        int i;
        unsigned char c;

        for (i = 0; i < bytes; i++) {
            if (rand_bytes_ex(libctx, &c, 1) <= 0)
                goto err;
            if (c >= 128 && i > 0)
                buf[i] = buf[i - 1];
            else if (c < 42)
                buf[i] = 0;
            else if (c < 84)
                buf[i] = 255;
        }
    }

    if (top >= 0) {
        if (top) {
            if (bit == 0) {
                buf[0] = 1;
                buf[1] |= 0x80;
            } else {
                buf[0] |= (3 << (bit - 1));
            }
        } else {
            buf[0] |= (1 << bit);
        }
    }
    buf[0] &= ~mask;
    if (bottom)                 /* set bottom bit if requested */
        buf[bytes - 1] |= 1;
    if (!BN_bin2bn(buf, bytes, rnd))
        goto err;
    ret = 1;
 err:
    OPENSSL_clear_free(buf, bytes);
    bn_check_top(rnd);
    return ret;

toosmall:
    BNerr(BN_F_BNRAND, BN_R_BITS_TOO_SMALL);
    return 0;
}