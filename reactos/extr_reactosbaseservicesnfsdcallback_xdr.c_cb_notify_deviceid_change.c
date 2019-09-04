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
typedef  int /*<<< orphan*/  uint32_t ;
struct notify_deviceid4 {int /*<<< orphan*/  immediate; scalar_t__ deviceid; int /*<<< orphan*/  layouttype; } ;
typedef  scalar_t__ bool_t ;
typedef  int /*<<< orphan*/  XDR ;

/* Variables and functions */
 int /*<<< orphan*/  CBX_ERR (char*) ; 
 int /*<<< orphan*/  PNFS_DEVICEID_SIZE ; 
 scalar_t__ xdr_bool (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ xdr_opaque (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 scalar_t__ xdr_u_int32_t (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static bool_t cb_notify_deviceid_change(XDR *xdr, struct notify_deviceid4 *change)
{
    bool_t result;

    result = xdr_u_int32_t(xdr, (uint32_t*)&change->layouttype);
    if (!result) { CBX_ERR("notify_deviceid.change.layouttype"); goto out; }

    result = xdr_opaque(xdr, (char*)change->deviceid, PNFS_DEVICEID_SIZE);
    if (!result) { CBX_ERR("notify_deviceid.change.deviceid"); goto out; }

    result = xdr_bool(xdr, &change->immediate);
    if (!result) { CBX_ERR("notify_deviceid.change.immediate"); goto out; }
out:
    return result;
}