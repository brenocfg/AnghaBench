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
struct TYPE_5__ {scalar_t__ status; int /*<<< orphan*/  reply; scalar_t__ cookieverf; } ;
typedef  TYPE_2__ nfs41_readdir_res ;
typedef  int /*<<< orphan*/  bool_t ;
typedef  int /*<<< orphan*/  XDR ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 scalar_t__ NFS4_OK ; 
 int /*<<< orphan*/  NFS4_VERIFIER_SIZE ; 
 int /*<<< orphan*/  OP_READDIR ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  decode_readdir_list (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ unexpected_op (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xdr_opaque (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xdr_u_int32_t (int /*<<< orphan*/ *,scalar_t__*) ; 

__attribute__((used)) static bool_t decode_op_readdir(
    XDR *xdr,
    nfs_resop4 *resop)
{
    nfs41_readdir_res *res = (nfs41_readdir_res*)resop->res;

    if (unexpected_op(resop->op, OP_READDIR))
        return FALSE;

    if (!xdr_u_int32_t(xdr, &res->status))
        return FALSE;

    if (res->status == NFS4_OK) {
        if (!xdr_opaque(xdr, (char *)res->cookieverf, NFS4_VERIFIER_SIZE))
            return FALSE;
        return decode_readdir_list(xdr, &res->reply);
    }
    return TRUE;
}