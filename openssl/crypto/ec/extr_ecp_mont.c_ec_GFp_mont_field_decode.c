#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/ * field_data1; } ;
typedef  TYPE_1__ EC_GROUP ;
typedef  int /*<<< orphan*/  BN_CTX ;
typedef  int /*<<< orphan*/  BIGNUM ;

/* Variables and functions */
 int BN_from_montgomery (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  EC_F_EC_GFP_MONT_FIELD_DECODE ; 
 int /*<<< orphan*/  EC_R_NOT_INITIALIZED ; 
 int /*<<< orphan*/  ECerr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int ec_GFp_mont_field_decode(const EC_GROUP *group, BIGNUM *r,
                             const BIGNUM *a, BN_CTX *ctx)
{
    if (group->field_data1 == NULL) {
        ECerr(EC_F_EC_GFP_MONT_FIELD_DECODE, EC_R_NOT_INITIALIZED);
        return 0;
    }

    return BN_from_montgomery(r, a, group->field_data1, ctx);
}