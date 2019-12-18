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
typedef  int /*<<< orphan*/  const BIGNUM ;

/* Variables and functions */
 int /*<<< orphan*/  BN_F_BN_GF2M_MOD ; 
 int BN_GF2m_mod_arr (int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,int*) ; 
 int BN_GF2m_poly2arr (int /*<<< orphan*/  const*,int*,scalar_t__) ; 
 int /*<<< orphan*/  BN_R_INVALID_LENGTH ; 
 int /*<<< orphan*/  BNerr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ OSSL_NELEM (int*) ; 
 int /*<<< orphan*/  bn_check_top (int /*<<< orphan*/  const*) ; 

int BN_GF2m_mod(BIGNUM *r, const BIGNUM *a, const BIGNUM *p)
{
    int ret = 0;
    int arr[6];
    bn_check_top(a);
    bn_check_top(p);
    ret = BN_GF2m_poly2arr(p, arr, OSSL_NELEM(arr));
    if (!ret || ret > (int)OSSL_NELEM(arr)) {
        BNerr(BN_F_BN_GF2M_MOD, BN_R_INVALID_LENGTH);
        return 0;
    }
    ret = BN_GF2m_mod_arr(r, a, arr);
    bn_check_top(r);
    return ret;
}