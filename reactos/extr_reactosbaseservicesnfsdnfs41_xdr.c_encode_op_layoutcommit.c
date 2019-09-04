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
struct TYPE_4__ {scalar_t__ new_time; int /*<<< orphan*/ * new_offset; int /*<<< orphan*/  stateid; int /*<<< orphan*/  length; int /*<<< orphan*/  offset; } ;
typedef  TYPE_1__ pnfs_layoutcommit_args ;
struct TYPE_5__ {int /*<<< orphan*/  op; scalar_t__ arg; } ;
typedef  TYPE_2__ nfs_argop4 ;
typedef  int /*<<< orphan*/  enum_t ;
typedef  int /*<<< orphan*/  bool_t ;
typedef  int /*<<< orphan*/  XDR ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  OP_LAYOUTCOMMIT ; 
 int /*<<< orphan*/  PNFS_LAYOUTTYPE_FILE ; 
 int /*<<< orphan*/  TRUE ; 
 scalar_t__ unexpected_op (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xdr_bool (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xdr_enum (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xdr_nfstime4 (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  xdr_stateid4 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xdr_u_hyper (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xdr_u_int32_t (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static bool_t encode_op_layoutcommit(
    XDR *xdr,
    nfs_argop4 *argop)
{
    pnfs_layoutcommit_args *args = (pnfs_layoutcommit_args*)argop->arg;
    bool_t false_bool = FALSE;
    bool_t true_bool = TRUE;
    enum_t pnfs_layout = PNFS_LAYOUTTYPE_FILE;
    uint32_t zero = 0;

    if (unexpected_op(argop->op, OP_LAYOUTCOMMIT))
        return FALSE;

    if (!xdr_u_hyper(xdr, &args->offset))
        return FALSE;

    if (!xdr_u_hyper(xdr, &args->length))
        return FALSE;

    if (!xdr_bool(xdr, &false_bool)) /* loca_reclaim = 0 */
        return FALSE;

    if (!xdr_stateid4(xdr, args->stateid))
        return FALSE;

    /* loca_last_write_offset */
    if (args->new_offset) {
        if (!xdr_bool(xdr, &true_bool))
            return FALSE;

        if (!xdr_u_hyper(xdr, args->new_offset))
            return FALSE;
    } else {
        if (!xdr_bool(xdr, &false_bool))
            return FALSE;
    }

    /* loca_time_modify */
    if (args->new_time) {
        if (!xdr_bool(xdr, &true_bool))
            return FALSE;

        if (!xdr_nfstime4(xdr, args->new_time))
            return FALSE;
    } else {
        if (!xdr_bool(xdr, &false_bool))
            return FALSE;
    }

    /* loca_layoutupdate */
    if (!xdr_enum(xdr, &pnfs_layout))
        return FALSE;

    return xdr_u_int32_t(xdr, &zero);
}