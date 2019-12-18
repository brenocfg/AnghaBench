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
typedef  int /*<<< orphan*/  xdrproc_t ;
struct TYPE_4__ {int /*<<< orphan*/  op; scalar_t__ res; } ;
typedef  TYPE_1__ nfs_resop4 ;
struct TYPE_5__ {scalar_t__ status; int /*<<< orphan*/  count; int /*<<< orphan*/ * secinfo; } ;
typedef  TYPE_2__ nfs41_secinfo_noname_res ;
typedef  int /*<<< orphan*/  nfs41_secinfo_info ;
typedef  int /*<<< orphan*/  bool_t ;
typedef  int /*<<< orphan*/  XDR ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  MAX_SECINFOS ; 
 scalar_t__ NFS4_OK ; 
 int /*<<< orphan*/  OP_SECINFO_NO_NAME ; 
 int /*<<< orphan*/  TRUE ; 
 scalar_t__ unexpected_op (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xdr_array (int /*<<< orphan*/ *,char**,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 scalar_t__ xdr_secinfo ; 
 int /*<<< orphan*/  xdr_u_int32_t (int /*<<< orphan*/ *,scalar_t__*) ; 

__attribute__((used)) static bool_t decode_op_secinfo_noname(
    XDR *xdr,
    nfs_resop4 *resop)
{
    nfs41_secinfo_noname_res *res = (nfs41_secinfo_noname_res *)resop->res;
    nfs41_secinfo_info *secinfo = res->secinfo;
    if (unexpected_op(resop->op, OP_SECINFO_NO_NAME))
        return FALSE;

    if (!xdr_u_int32_t(xdr, &res->status))
        return FALSE;

    if (res->status == NFS4_OK)
        return xdr_array(xdr, (char**)&secinfo, &res->count,
            MAX_SECINFOS, sizeof(nfs41_secinfo_info), (xdrproc_t)xdr_secinfo);

    return TRUE;
}