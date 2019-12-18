#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u_int32_t ;
struct TYPE_6__ {int /*<<< orphan*/  notification; TYPE_3__* device; } ;
typedef  TYPE_2__ pnfs_getdeviceinfo_res_ok ;
typedef  int /*<<< orphan*/  enum_t ;
typedef  int /*<<< orphan*/  bool_t ;
typedef  int /*<<< orphan*/  XDR ;
struct TYPE_5__ {scalar_t__ type; } ;
struct TYPE_7__ {TYPE_1__ device; } ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 scalar_t__ PNFS_LAYOUTTYPE_FILE ; 
 int /*<<< orphan*/  xdr_bitmap4 (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xdr_enum (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xdr_file_device (int /*<<< orphan*/ *,TYPE_3__*) ; 
 int /*<<< orphan*/  xdr_u_int32_t (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static bool_t decode_getdeviceinfo_ok(
    XDR *xdr,
    pnfs_getdeviceinfo_res_ok *res_ok)
{
    u_int32_t len_ignored;

    if (!xdr_enum(xdr, (enum_t *)&res_ok->device->device.type))
        return FALSE;

    if (res_ok->device->device.type != PNFS_LAYOUTTYPE_FILE)
        return FALSE;

    if (!xdr_u_int32_t(xdr, &len_ignored))
        return FALSE;

    if (!xdr_file_device(xdr, res_ok->device))
        return FALSE;

    return xdr_bitmap4(xdr, &res_ok->notification);
}