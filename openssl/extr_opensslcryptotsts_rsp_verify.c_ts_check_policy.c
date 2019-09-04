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
struct TYPE_3__ {int /*<<< orphan*/ * policy_id; } ;
typedef  TYPE_1__ TS_TST_INFO ;
typedef  int /*<<< orphan*/  ASN1_OBJECT ;

/* Variables and functions */
 scalar_t__ OBJ_cmp (int /*<<< orphan*/  const*,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  TS_F_TS_CHECK_POLICY ; 
 int /*<<< orphan*/  TS_R_POLICY_MISMATCH ; 
 int /*<<< orphan*/  TSerr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ts_check_policy(const ASN1_OBJECT *req_oid,
                           const TS_TST_INFO *tst_info)
{
    const ASN1_OBJECT *resp_oid = tst_info->policy_id;

    if (OBJ_cmp(req_oid, resp_oid) != 0) {
        TSerr(TS_F_TS_CHECK_POLICY, TS_R_POLICY_MISMATCH);
        return 0;
    }

    return 1;
}