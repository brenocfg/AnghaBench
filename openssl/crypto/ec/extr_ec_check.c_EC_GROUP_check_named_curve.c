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
typedef  int /*<<< orphan*/  EC_GROUP ;
typedef  int /*<<< orphan*/  BN_CTX ;

/* Variables and functions */
 int /*<<< orphan*/  BN_CTX_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * BN_CTX_new () ; 
 int /*<<< orphan*/  EC_F_EC_GROUP_CHECK_NAMED_CURVE ; 
 int /*<<< orphan*/ * EC_curve_nid2nist (int) ; 
 int /*<<< orphan*/  ECerr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ERR_R_MALLOC_FAILURE ; 
 int NID_undef ; 
 int ec_curve_nid_from_params (int /*<<< orphan*/  const*,int /*<<< orphan*/ *) ; 

int EC_GROUP_check_named_curve(const EC_GROUP *group, int nist_only,
                               BN_CTX *ctx)
{
    int nid = NID_undef;
#ifndef FIPS_MODE
    BN_CTX *new_ctx = NULL;

    if (ctx == NULL) {
        ctx = new_ctx = BN_CTX_new();
        if (ctx == NULL) {
            ECerr(EC_F_EC_GROUP_CHECK_NAMED_CURVE, ERR_R_MALLOC_FAILURE);
            goto err;
        }
    }
#endif

    nid = ec_curve_nid_from_params(group, ctx);
    if (nid > 0 && nist_only && EC_curve_nid2nist(nid) == NULL)
        nid = NID_undef;

#ifndef FIPS_MODE
 err:
    BN_CTX_free(ctx);
#endif
    return nid;
}