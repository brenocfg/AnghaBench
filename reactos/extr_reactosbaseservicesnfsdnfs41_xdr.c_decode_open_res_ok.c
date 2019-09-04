#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {TYPE_2__* delegation; int /*<<< orphan*/  attrset; int /*<<< orphan*/  rflags; int /*<<< orphan*/  cinfo; int /*<<< orphan*/  stateid; } ;
typedef  TYPE_1__ nfs41_op_open_res_ok ;
typedef  int /*<<< orphan*/  enum_t ;
typedef  int /*<<< orphan*/  bool_t ;
typedef  int /*<<< orphan*/  XDR ;
struct TYPE_7__ {int type; } ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
#define  OPEN_DELEGATE_NONE 131 
#define  OPEN_DELEGATE_NONE_EXT 130 
#define  OPEN_DELEGATE_READ 129 
#define  OPEN_DELEGATE_WRITE 128 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  decode_open_none_delegation4 (int /*<<< orphan*/ *,TYPE_2__*) ; 
 int /*<<< orphan*/  decode_open_read_delegation4 (int /*<<< orphan*/ *,TYPE_2__*) ; 
 int /*<<< orphan*/  decode_open_write_delegation4 (int /*<<< orphan*/ *,TYPE_2__*) ; 
 int /*<<< orphan*/  eprintf (char*,int) ; 
 int /*<<< orphan*/  xdr_bitmap4 (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xdr_change_info4 (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xdr_enum (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xdr_stateid4 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xdr_u_int32_t (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static bool_t decode_open_res_ok(
    XDR *xdr,
    nfs41_op_open_res_ok *res)
{
    if (!xdr_stateid4(xdr, res->stateid))
        return FALSE;

    if (!xdr_change_info4(xdr, &res->cinfo))
        return FALSE;

    if (!xdr_u_int32_t(xdr, &res->rflags))
        return FALSE;

    if (!xdr_bitmap4(xdr, &res->attrset))
        return FALSE;

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