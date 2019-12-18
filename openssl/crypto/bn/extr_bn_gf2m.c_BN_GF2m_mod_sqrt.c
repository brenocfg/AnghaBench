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
typedef  int /*<<< orphan*/  BN_CTX ;
typedef  int /*<<< orphan*/  const BIGNUM ;

/* Variables and functions */
 int /*<<< orphan*/  BN_F_BN_GF2M_MOD_SQRT ; 
 int BN_GF2m_mod_sqrt_arr (int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,int*,int /*<<< orphan*/ *) ; 
 int BN_GF2m_poly2arr (int /*<<< orphan*/  const*,int*,int const) ; 
 int /*<<< orphan*/  BN_R_INVALID_LENGTH ; 
 int BN_num_bits (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  BNerr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OPENSSL_free (int*) ; 
 int* OPENSSL_malloc (int) ; 
 int /*<<< orphan*/  bn_check_top (int /*<<< orphan*/  const*) ; 

int BN_GF2m_mod_sqrt(BIGNUM *r, const BIGNUM *a, const BIGNUM *p, BN_CTX *ctx)
{
    int ret = 0;
    const int max = BN_num_bits(p) + 1;
    int *arr = NULL;
    bn_check_top(a);
    bn_check_top(p);
    if ((arr = OPENSSL_malloc(sizeof(*arr) * max)) == NULL)
        goto err;
    ret = BN_GF2m_poly2arr(p, arr, max);
    if (!ret || ret > max) {
        BNerr(BN_F_BN_GF2M_MOD_SQRT, BN_R_INVALID_LENGTH);
        goto err;
    }
    ret = BN_GF2m_mod_sqrt_arr(r, a, arr, ctx);
    bn_check_top(r);
 err:
    OPENSSL_free(arr);
    return ret;
}