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
typedef  scalar_t__ uint32_t ;
struct TYPE_4__ {int /*<<< orphan*/  op; scalar_t__ res; } ;
typedef  TYPE_1__ nfs_resop4 ;
struct TYPE_5__ {scalar_t__ csr_sequence; scalar_t__ csr_flags; int /*<<< orphan*/  csr_back_chan_attrs; int /*<<< orphan*/  csr_fore_chan_attrs; scalar_t__ csr_sessionid; } ;
typedef  TYPE_2__ nfs41_create_session_res ;
typedef  int /*<<< orphan*/  bool_t ;
typedef  int /*<<< orphan*/  XDR ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 scalar_t__ NFS4_OK ; 
 int /*<<< orphan*/  NFS4_SESSIONID_SIZE ; 
 int /*<<< orphan*/  OP_CREATE_SESSION ; 
 int /*<<< orphan*/  TRUE ; 
 scalar_t__ unexpected_op (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xdr_channel_attrs4 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xdr_opaque (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xdr_u_int32_t (int /*<<< orphan*/ *,scalar_t__*) ; 

__attribute__((used)) static bool_t decode_op_create_session(
    XDR *xdr,
    nfs_resop4 *resop)
{
    uint32_t opstatus;
    nfs41_create_session_res *res = (nfs41_create_session_res*)resop->res;

    if (unexpected_op(resop->op, OP_CREATE_SESSION))
        return FALSE;

    if (!xdr_u_int32_t(xdr, &opstatus))
        return FALSE;

    if (opstatus != NFS4_OK)
        return TRUE;

    if (!xdr_opaque(xdr, (char *)res->csr_sessionid, NFS4_SESSIONID_SIZE))
        return FALSE;

    /* sequenceid4 csr_sequence */
    if (!xdr_u_int32_t(xdr, &res->csr_sequence))
        return FALSE;

    /* uint32_t csr_flags */
    if (!xdr_u_int32_t(xdr, &res->csr_flags))
        return FALSE;

    /* channel_attrs4 csr_fore_chan_attrs */
    if (!xdr_channel_attrs4(xdr, res->csr_fore_chan_attrs))
        return FALSE;

    /* channel_attrs4 csr_back_chan_attrs */
    return xdr_channel_attrs4(xdr, res->csr_back_chan_attrs);
}