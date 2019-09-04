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
struct cb_notify_lock_res {int /*<<< orphan*/  status; } ;
typedef  int /*<<< orphan*/  bool_t ;
typedef  int /*<<< orphan*/  XDR ;

/* Variables and functions */
 int /*<<< orphan*/  CBX_ERR (char*) ; 
 int /*<<< orphan*/  xdr_enum (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static bool_t op_cb_notify_lock_res(XDR *xdr, struct cb_notify_lock_res *res)
{
    bool_t result;

    result = xdr_enum(xdr, &res->status);
    if (!result) { CBX_ERR("notify_lock.status"); goto out; }
out:
    return result;
}