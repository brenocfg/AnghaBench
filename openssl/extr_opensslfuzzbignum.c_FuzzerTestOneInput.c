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
typedef  size_t uint8_t ;
typedef  int /*<<< orphan*/  BN_CTX ;
typedef  int /*<<< orphan*/  BIGNUM ;

/* Variables and functions */
 int /*<<< orphan*/  BN_CTX_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * BN_CTX_new () ; 
 int /*<<< orphan*/ * BN_bin2bn (size_t const*,size_t,int /*<<< orphan*/ *) ; 
 scalar_t__ BN_cmp (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  BN_free (int /*<<< orphan*/ *) ; 
 scalar_t__ BN_is_zero (int /*<<< orphan*/ *) ; 
 int BN_mod_exp (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int BN_mod_exp_simple (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * BN_new () ; 
 int /*<<< orphan*/  BN_print_fp (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  BN_set_negative (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  ERR_clear_error () ; 
 int /*<<< orphan*/  OPENSSL_assert (int) ; 
 int /*<<< orphan*/  putchar (char) ; 
 int /*<<< orphan*/  stdout ; 

int FuzzerTestOneInput(const uint8_t *buf, size_t len)
{
    int success = 0;
    size_t l1 = 0, l2 = 0, l3 = 0;
    int s1 = 0, s3 = 0;
    BN_CTX *ctx;
    BIGNUM *b1;
    BIGNUM *b2;
    BIGNUM *b3;
    BIGNUM *b4;
    BIGNUM *b5;

    b1 = BN_new();
    b2 = BN_new();
    b3 = BN_new();
    b4 = BN_new();
    b5 = BN_new();
    ctx = BN_CTX_new();

    /* Divide the input into three parts, using the values of the first two
     * bytes to choose lengths, which generate b1, b2 and b3. Use three bits
     * of the third byte to choose signs for the three numbers.
     */
    if (len > 2) {
        len -= 3;
        l1 = (buf[0] * len) / 255;
        ++buf;
        l2 = (buf[0] * (len - l1)) / 255;
        ++buf;
        l3 = len - l1 - l2;

        s1 = buf[0] & 1;
        s3 = buf[0] & 4;
        ++buf;
    }
    OPENSSL_assert(BN_bin2bn(buf, l1, b1) == b1);
    BN_set_negative(b1, s1);
    OPENSSL_assert(BN_bin2bn(buf + l1, l2, b2) == b2);
    OPENSSL_assert(BN_bin2bn(buf + l1 + l2, l3, b3) == b3);
    BN_set_negative(b3, s3);

    /* mod 0 is undefined */
    if (BN_is_zero(b3)) {
        success = 1;
        goto done;
    }

    OPENSSL_assert(BN_mod_exp(b4, b1, b2, b3, ctx));
    OPENSSL_assert(BN_mod_exp_simple(b5, b1, b2, b3, ctx));

    success = BN_cmp(b4, b5) == 0;
    if (!success) {
        BN_print_fp(stdout, b1);
        putchar('\n');
        BN_print_fp(stdout, b2);
        putchar('\n');
        BN_print_fp(stdout, b3);
        putchar('\n');
        BN_print_fp(stdout, b4);
        putchar('\n');
        BN_print_fp(stdout, b5);
        putchar('\n');
    }

 done:
    OPENSSL_assert(success);
    BN_free(b1);
    BN_free(b2);
    BN_free(b3);
    BN_free(b4);
    BN_free(b5);
    BN_CTX_free(ctx);
    ERR_clear_error();

    return 0;
}