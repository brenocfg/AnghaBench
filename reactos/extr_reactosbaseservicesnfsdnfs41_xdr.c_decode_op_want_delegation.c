#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  op; scalar_t__ res; } ;
typedef  TYPE_1__ nfs_resop4 ;
struct TYPE_8__ {TYPE_3__* delegation; scalar_t__ status; } ;
typedef  TYPE_2__ nfs41_want_delegation_res ;
typedef  int /*<<< orphan*/  enum_t ;
typedef  int /*<<< orphan*/  bool_t ;
typedef  int /*<<< orphan*/  XDR ;
struct TYPE_9__ {int type; } ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
#define  OPEN_DELEGATE_NONE 131 
#define  OPEN_DELEGATE_NONE_EXT 130 
#define  OPEN_DELEGATE_READ 129 
#define  OPEN_DELEGATE_WRITE 128 
 int /*<<< orphan*/  OP_WANT_DELEGATION ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  decode_open_none_delegation4 (int /*<<< orphan*/ *,TYPE_3__*) ; 
 int /*<<< orphan*/  decode_open_read_delegation4 (int /*<<< orphan*/ *,TYPE_3__*) ; 
 int /*<<< orphan*/  decode_open_write_delegation4 (int /*<<< orphan*/ *,TYPE_3__*) ; 
 int /*<<< orphan*/  eprintf (char*,int) ; 
 scalar_t__ unexpected_op (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xdr_enum (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xdr_u_int32_t (int /*<<< orphan*/ *,scalar_t__*) ; 

__attribute__((used)) static bool_t decode_op_want_delegation(
    XDR *xdr,
    nfs_resop4 *resop)
{
    nfs41_want_delegation_res *res = (nfs41_want_delegation_res*)resop->res;

    if (unexpected_op(resop->op, OP_WANT_DELEGATION))
        return FALSE;

    if (!xdr_u_int32_t(xdr, &res->status))
        return FALSE;

    if (res->status)
        return TRUE;

    if (!xdr_enum(xdr, (enum_t*)&res->delegation->type))
        return FALSE;

    switch (res->delegation->type)
    {
    case OPEN_DELEGATE_NONE:
        return TRUE;
    case OPEN_DELEGATE_NONE_EXT:
        return decode_open_none_delegation4(xdr, res->delegation);
    case OPEN_DELEGATE_READ:
        return decode_open_read_delegation4(xdr, res->delegation);
    case OPEN_DELEGATE_WRITE:
        return decode_open_write_delegation4(xdr, res->delegation);
    default:
        eprintf("decode_open_res_ok: delegation type %d not "
            "supported.\n", res->delegation->type);
        return FALSE;
    }
}