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
struct TYPE_5__ {scalar_t__ status; scalar_t__ sequenceid; scalar_t__ flags; int /*<<< orphan*/  server_scope_len; int /*<<< orphan*/  server_owner; int /*<<< orphan*/  state_protect; int /*<<< orphan*/  clientid; scalar_t__ server_scope; } ;
typedef  TYPE_2__ nfs41_exchange_id_res ;
typedef  int /*<<< orphan*/  bool_t ;
typedef  int /*<<< orphan*/  XDR ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 scalar_t__ NFS4_OK ; 
 int /*<<< orphan*/  NFS4_OPAQUE_LIMIT ; 
 int /*<<< orphan*/  OP_EXCHANGE_ID ; 
 int /*<<< orphan*/  TRUE ; 
 scalar_t__ unexpected_op (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xdr_bytes (int /*<<< orphan*/ *,char**,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xdr_server_owner4 (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xdr_state_protect4_r (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xdr_u_hyper (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xdr_u_int32_t (int /*<<< orphan*/ *,scalar_t__*) ; 

__attribute__((used)) static bool_t decode_op_exchange_id(
    XDR *xdr,
    nfs_resop4 *resop)
{
    nfs41_exchange_id_res *res = (nfs41_exchange_id_res*)resop->res;
    char *server_scope = (char *)res->server_scope;

    if (unexpected_op(resop->op, OP_EXCHANGE_ID))
        return FALSE;

    if (!xdr_u_int32_t(xdr, &res->status))
        return FALSE;

    if (res->status != NFS4_OK)
        return TRUE;

    if (!xdr_u_hyper(xdr, &res->clientid))
        return FALSE;

    if (!xdr_u_int32_t(xdr, &res->sequenceid))
        return FALSE;

    if (!xdr_u_int32_t(xdr, &res->flags))
        return FALSE;

    if (!xdr_state_protect4_r(xdr, &res->state_protect))
        return FALSE;

    if (!xdr_server_owner4(xdr, &res->server_owner))
        return FALSE;

    return xdr_bytes(xdr, &server_scope,
        &res->server_scope_len, NFS4_OPAQUE_LIMIT);
}