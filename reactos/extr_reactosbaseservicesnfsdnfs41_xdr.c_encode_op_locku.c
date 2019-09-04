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
struct TYPE_7__ {int /*<<< orphan*/  length; int /*<<< orphan*/  offset; TYPE_1__* lock_stateid; int /*<<< orphan*/  seqid; int /*<<< orphan*/  locktype; } ;
typedef  TYPE_3__ nfs41_locku_args ;
typedef  int /*<<< orphan*/  bool_t ;
typedef  int /*<<< orphan*/  XDR ;
struct TYPE_5__ {int /*<<< orphan*/  stateid; } ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  OP_LOCKU ; 
 scalar_t__ unexpected_op (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xdr_stateid4 (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xdr_u_hyper (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xdr_u_int32_t (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static bool_t encode_op_locku(
    XDR *xdr,
    nfs_argop4 *argop)
{
    nfs41_locku_args *args = (nfs41_locku_args*)argop->arg;

    if (unexpected_op(argop->op, OP_LOCKU))
        return FALSE;

    if (!xdr_u_int32_t(xdr, &args->locktype))
        return FALSE;

    if (!xdr_u_int32_t(xdr, &args->seqid))
        return FALSE;

    if (!xdr_stateid4(xdr, &args->lock_stateid->stateid))
        return FALSE;

    if (!xdr_u_hyper(xdr, &args->offset))
        return FALSE;

    return xdr_u_hyper(xdr, &args->length);
}