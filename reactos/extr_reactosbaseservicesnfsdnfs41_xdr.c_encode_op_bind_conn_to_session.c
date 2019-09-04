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
typedef  int /*<<< orphan*/  uint32_t ;
struct TYPE_4__ {int /*<<< orphan*/  op; scalar_t__ arg; } ;
typedef  TYPE_1__ nfs_argop4 ;
struct TYPE_5__ {int /*<<< orphan*/  dir; scalar_t__ sessionid; } ;
typedef  TYPE_2__ nfs41_bind_conn_to_session_args ;
typedef  int /*<<< orphan*/  enum_t ;
typedef  int /*<<< orphan*/  bool_t ;
typedef  int /*<<< orphan*/  XDR ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  NFS4_SESSIONID_SIZE ; 
 int /*<<< orphan*/  OP_BIND_CONN_TO_SESSION ; 
 scalar_t__ unexpected_op (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xdr_enum (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xdr_opaque (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xdr_u_int32_t (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static bool_t encode_op_bind_conn_to_session(
    XDR *xdr,
    nfs_argop4 *argop)
{
    uint32_t zero = 0;

    nfs41_bind_conn_to_session_args *args =
        (nfs41_bind_conn_to_session_args*)argop->arg;

    if (unexpected_op(argop->op, OP_BIND_CONN_TO_SESSION))
        return FALSE;

    if (!xdr_opaque(xdr, (char *)args->sessionid, NFS4_SESSIONID_SIZE))
        return FALSE;

    if (!xdr_enum(xdr, (enum_t *)&args->dir))
        return FALSE;

    return xdr_u_int32_t(xdr, &zero); /* bctsa_use_conn_in_rdma_mode = false */
}