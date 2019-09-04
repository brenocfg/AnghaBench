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
struct TYPE_6__ {int /*<<< orphan*/  op; scalar_t__ arg; } ;
typedef  TYPE_2__ nfs_argop4 ;
struct TYPE_5__ {scalar_t__ verf; int /*<<< orphan*/  cookie; } ;
struct TYPE_7__ {int /*<<< orphan*/  attr_request; int /*<<< orphan*/  maxcount; int /*<<< orphan*/  dircount; TYPE_1__ cookie; } ;
typedef  TYPE_3__ nfs41_readdir_args ;
typedef  int /*<<< orphan*/  bool_t ;
typedef  int /*<<< orphan*/  XDR ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  NFS4_VERIFIER_SIZE ; 
 int /*<<< orphan*/  OP_READDIR ; 
 scalar_t__ unexpected_op (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xdr_bitmap4 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xdr_opaque (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xdr_u_hyper (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xdr_u_int32_t (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static bool_t encode_op_readdir(
    XDR *xdr,
    nfs_argop4 *argop)
{
    nfs41_readdir_args *args = (nfs41_readdir_args*)argop->arg;

    if (unexpected_op(argop->op, OP_READDIR))
        return FALSE;

    if (!xdr_u_hyper(xdr, &args->cookie.cookie))
        return FALSE;

    if (!xdr_opaque(xdr, (char *)args->cookie.verf, NFS4_VERIFIER_SIZE))
        return FALSE;

    if (!xdr_u_int32_t(xdr, &args->dircount))
        return FALSE;

    if (!xdr_u_int32_t(xdr, &args->maxcount))
        return FALSE;

    return xdr_bitmap4(xdr, args->attr_request);
}