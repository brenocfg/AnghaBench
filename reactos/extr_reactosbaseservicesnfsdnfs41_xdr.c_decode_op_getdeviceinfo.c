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
typedef  int /*<<< orphan*/  uint32_t ;
struct TYPE_5__ {int /*<<< orphan*/  res_ok; } ;
struct TYPE_6__ {int status; TYPE_1__ u; } ;
typedef  TYPE_2__ pnfs_getdeviceinfo_res ;
struct TYPE_7__ {int /*<<< orphan*/  op; scalar_t__ res; } ;
typedef  TYPE_3__ nfs_resop4 ;
typedef  int /*<<< orphan*/  bool_t ;
typedef  int /*<<< orphan*/  XDR ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
#define  NFS4ERR_TOOSMALL 129 
#define  NFS4_OK 128 
 int /*<<< orphan*/  OP_GETDEVICEINFO ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  decode_getdeviceinfo_ok (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ unexpected_op (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xdr_u_int32_t (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static bool_t decode_op_getdeviceinfo(
    XDR *xdr,
    nfs_resop4 *resop)
{
    pnfs_getdeviceinfo_res *res = (pnfs_getdeviceinfo_res*)resop->res;

    if (unexpected_op(resop->op, OP_GETDEVICEINFO))
        return FALSE;

    if (!xdr_u_int32_t(xdr, (uint32_t *)&res->status))
        return FALSE;

    switch (res->status) {
    case NFS4_OK:
        return decode_getdeviceinfo_ok(xdr, &res->u.res_ok);
        break;
    case NFS4ERR_TOOSMALL:
        {
            uint32_t ignored;
            return xdr_u_int32_t(xdr, &ignored);
        }
        break;
    }
    return TRUE;
}