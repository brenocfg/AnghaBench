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
typedef  int /*<<< orphan*/  u_int32_t ;
struct TYPE_4__ {scalar_t__ return_type; int /*<<< orphan*/  stateid; int /*<<< orphan*/  length; int /*<<< orphan*/  offset; int /*<<< orphan*/  iomode; int /*<<< orphan*/  type; int /*<<< orphan*/  reclaim; } ;
typedef  TYPE_1__ pnfs_layoutreturn_args ;
struct TYPE_5__ {int /*<<< orphan*/  op; scalar_t__ arg; } ;
typedef  TYPE_2__ nfs_argop4 ;
typedef  int /*<<< orphan*/  enum_t ;
typedef  int /*<<< orphan*/  bool_t ;
typedef  int /*<<< orphan*/  XDR ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  OP_LAYOUTRETURN ; 
 scalar_t__ PNFS_RETURN_FILE ; 
 int /*<<< orphan*/  eprintf (char*,char*,scalar_t__) ; 
 scalar_t__ unexpected_op (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xdr_bool (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xdr_enum (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xdr_stateid4 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xdr_u_hyper (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xdr_u_int32_t (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static bool_t encode_op_layoutreturn(
    XDR *xdr,
    nfs_argop4 *argop)
{
    pnfs_layoutreturn_args *args = (pnfs_layoutreturn_args*)argop->arg;

    if (unexpected_op(argop->op, OP_LAYOUTRETURN))
        return FALSE;

    if (!xdr_bool(xdr, &args->reclaim))
        return FALSE;

    if (!xdr_enum(xdr, (enum_t *)&args->type))
        return FALSE;

    if (!xdr_enum(xdr, (enum_t *)&args->iomode))
        return FALSE;

    if (!xdr_enum(xdr, (enum_t *)&args->return_type))
        return FALSE;

    if (args->return_type == PNFS_RETURN_FILE) {
        u_int32_t zero = 0;

        if (!xdr_u_hyper(xdr, &args->offset))
            return FALSE;

        if (!xdr_u_hyper(xdr, &args->length))
            return FALSE;

        if (!xdr_stateid4(xdr, args->stateid))
            return FALSE;

        return xdr_u_int32_t(xdr, &zero); /* size of lrf_body is 0 */
    } else {
        eprintf("%s: layout type (%d) is not PNFS_RETURN_FILE!\n",
            "encode_op_layoutreturn", args->return_type);
        return FALSE;
    }
}