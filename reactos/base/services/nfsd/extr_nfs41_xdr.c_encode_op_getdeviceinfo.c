#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  notify_types; int /*<<< orphan*/  maxcount; int /*<<< orphan*/  layout_type; scalar_t__ deviceid; } ;
typedef  TYPE_1__ pnfs_getdeviceinfo_args ;
struct TYPE_5__ {int /*<<< orphan*/  op; scalar_t__ arg; } ;
typedef  TYPE_2__ nfs_argop4 ;
typedef  int /*<<< orphan*/  enum_t ;
typedef  int /*<<< orphan*/  bool_t ;
typedef  int /*<<< orphan*/  XDR ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  OP_GETDEVICEINFO ; 
 int /*<<< orphan*/  PNFS_DEVICEID_SIZE ; 
 scalar_t__ unexpected_op (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xdr_bitmap4 (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xdr_enum (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xdr_opaque (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xdr_u_int32_t (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static bool_t encode_op_getdeviceinfo(
    XDR *xdr,
    nfs_argop4 *argop)
{
    pnfs_getdeviceinfo_args *args = (pnfs_getdeviceinfo_args*)argop->arg;

    if (unexpected_op(argop->op, OP_GETDEVICEINFO))
        return FALSE;

    if (!xdr_opaque(xdr, (char *)args->deviceid, PNFS_DEVICEID_SIZE))
        return FALSE;

    if (!xdr_enum(xdr, (enum_t *)&args->layout_type))
        return FALSE;

    if (!xdr_u_int32_t(xdr, &args->maxcount))
        return FALSE;

    return xdr_bitmap4(xdr, &args->notify_types);
}