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
struct TYPE_4__ {int /*<<< orphan*/  op; scalar_t__ res; } ;
typedef  TYPE_1__ nfs_resop4 ;
struct TYPE_5__ {scalar_t__ status; int /*<<< orphan*/  dir; } ;
typedef  TYPE_2__ nfs41_bind_conn_to_session_res ;
typedef  int /*<<< orphan*/  enum_t ;
typedef  int /*<<< orphan*/  bool_t ;
typedef  int /*<<< orphan*/  XDR ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 scalar_t__ NFS4_OK ; 
 int NFS4_SESSIONID_SIZE ; 
 int /*<<< orphan*/  OP_BIND_CONN_TO_SESSION ; 
 int /*<<< orphan*/  TRUE ; 
 scalar_t__ unexpected_op (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xdr_bool (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xdr_enum (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xdr_opaque (int /*<<< orphan*/ *,char*,int) ; 

__attribute__((used)) static bool_t decode_op_bind_conn_to_session(
    XDR *xdr,
    nfs_resop4 *resop)
{
    unsigned char sessionid_ignored[NFS4_SESSIONID_SIZE];
    nfs41_bind_conn_to_session_res *res =
        (nfs41_bind_conn_to_session_res*)resop->res;
    bool_t use_rdma_ignored;

    if (unexpected_op(resop->op, OP_BIND_CONN_TO_SESSION))
        return FALSE;

    if (!xdr_enum(xdr, (enum_t *)&res->status))
        return FALSE;

    if (res->status == NFS4_OK) {
        if (!xdr_opaque(xdr, (char *)&sessionid_ignored, NFS4_SESSIONID_SIZE))
            return FALSE;

        if (!xdr_enum(xdr, (enum_t *)&res->dir))
            return FALSE;

        return xdr_bool(xdr, &use_rdma_ignored);
    }
    return TRUE;
}