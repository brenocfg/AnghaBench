#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  xdrproc_t ;
struct cb_compound_args {int /*<<< orphan*/  argarray_count; int /*<<< orphan*/  argarray; int /*<<< orphan*/  callback_ident; int /*<<< orphan*/  minorversion; int /*<<< orphan*/  tag; } ;
struct cb_argop {int dummy; } ;
typedef  scalar_t__ bool_t ;
typedef  int /*<<< orphan*/  XDR ;

/* Variables and functions */
 int /*<<< orphan*/  CBX_ERR (char*) ; 
 int /*<<< orphan*/  CB_COMPOUND_MAX_OPERATIONS ; 
 scalar_t__ cb_compound_argop ; 
 scalar_t__ cb_compound_tag (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ xdr_array (int /*<<< orphan*/ *,char**,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 scalar_t__ xdr_u_int32_t (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

bool_t proc_cb_compound_args(XDR *xdr, struct cb_compound_args *args)
{
    bool_t result;

    result = cb_compound_tag(xdr, &args->tag);
    if (!result) { CBX_ERR("compound.tag"); goto out; }

    result = xdr_u_int32_t(xdr, &args->minorversion);
    if (!result) { CBX_ERR("compound.minorversion"); goto out; }

    /* "superfluous in NFSv4.1 and MUST be ignored by the client" */
    result = xdr_u_int32_t(xdr, &args->callback_ident);
    if (!result) { CBX_ERR("compound.callback_ident"); goto out; }

    result = xdr_array(xdr, (char**)&args->argarray,
        &args->argarray_count, CB_COMPOUND_MAX_OPERATIONS,
        sizeof(struct cb_argop), (xdrproc_t)cb_compound_argop);
    if (!result) { CBX_ERR("compound.argarray"); goto out; }
out:
    return result;
}