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
typedef  int /*<<< orphan*/  RSA ;
typedef  int /*<<< orphan*/  BN_GENCB ;
typedef  int /*<<< orphan*/  BIGNUM ;

/* Variables and functions */
 int /*<<< orphan*/  BN_GENCB_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * BN_GENCB_new () ; 
 int /*<<< orphan*/  BN_GENCB_set_old (int /*<<< orphan*/ *,void (*) (int,int,void*),void*) ; 
 int /*<<< orphan*/  BN_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * BN_new () ; 
 scalar_t__ BN_set_bit (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  RSA_free (int /*<<< orphan*/ *) ; 
 scalar_t__ RSA_generate_key_ex (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * RSA_new () ; 

RSA *RSA_generate_key(int bits, unsigned long e_value,
                      void (*callback) (int, int, void *), void *cb_arg)
{
    int i;
    BN_GENCB *cb = BN_GENCB_new();
    RSA *rsa = RSA_new();
    BIGNUM *e = BN_new();

    if (cb == NULL || rsa == NULL || e == NULL)
        goto err;

    /*
     * The problem is when building with 8, 16, or 32 BN_ULONG, unsigned long
     * can be larger
     */
    for (i = 0; i < (int)sizeof(unsigned long) * 8; i++) {
        if (e_value & (1UL << i))
            if (BN_set_bit(e, i) == 0)
                goto err;
    }

    BN_GENCB_set_old(cb, callback, cb_arg);

    if (RSA_generate_key_ex(rsa, bits, e, cb)) {
        BN_free(e);
        BN_GENCB_free(cb);
        return rsa;
    }
 err:
    BN_free(e);
    RSA_free(rsa);
    BN_GENCB_free(cb);
    return 0;
}