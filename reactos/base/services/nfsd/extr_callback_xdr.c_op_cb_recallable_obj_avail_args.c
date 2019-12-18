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
struct cb_recallable_obj_avail_args {int /*<<< orphan*/  target_highest_slotid; } ;
typedef  int /*<<< orphan*/  bool_t ;
typedef  int /*<<< orphan*/  XDR ;

/* Variables and functions */
 int /*<<< orphan*/  CBX_ERR (char*) ; 
 int /*<<< orphan*/  xdr_u_int32_t (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static bool_t op_cb_recallable_obj_avail_args(XDR *xdr, struct cb_recallable_obj_avail_args *res)
{
    bool_t result;

    result = xdr_u_int32_t(xdr, &res->target_highest_slotid);
    if (!result) { CBX_ERR("recallable_obj_avail.target_highest_slotid"); goto out; }
out:
    return result;
}