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
struct cb_sequence_ref_list {int dummy; } ;
struct cb_sequence_args {int /*<<< orphan*/  ref_list_count; int /*<<< orphan*/  ref_lists; int /*<<< orphan*/  cachethis; int /*<<< orphan*/  highest_slotid; int /*<<< orphan*/  slotid; int /*<<< orphan*/  sequenceid; int /*<<< orphan*/  sessionid; } ;
typedef  scalar_t__ bool_t ;
typedef  int /*<<< orphan*/  XDR ;

/* Variables and functions */
 int /*<<< orphan*/  CBX_ERR (char*) ; 
 int /*<<< orphan*/  NFS4_SESSIONID_SIZE ; 
 scalar_t__ op_cb_sequence_ref_list ; 
 scalar_t__ xdr_array (int /*<<< orphan*/ *,char**,int /*<<< orphan*/ *,int,int,int /*<<< orphan*/ ) ; 
 scalar_t__ xdr_bool (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ xdr_opaque (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ xdr_u_int32_t (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static bool_t op_cb_sequence_args(XDR *xdr, struct cb_sequence_args *args)
{
    bool_t result;

    result = xdr_opaque(xdr, args->sessionid, NFS4_SESSIONID_SIZE);
    if (!result) { CBX_ERR("sequence_args.sessionid"); goto out; }

    result = xdr_u_int32_t(xdr, &args->sequenceid);
    if (!result) { CBX_ERR("sequence_args.sequenceid"); goto out; }

    result = xdr_u_int32_t(xdr, &args->slotid);
    if (!result) { CBX_ERR("sequence_args.slotid"); goto out; }

    result = xdr_u_int32_t(xdr, &args->highest_slotid);
    if (!result) { CBX_ERR("sequence_args.highest_slotid"); goto out; }

    result = xdr_bool(xdr, &args->cachethis);
    if (!result) { CBX_ERR("sequence_args.cachethis"); goto out; }

    result = xdr_array(xdr, (char**)&args->ref_lists,
        &args->ref_list_count, 64, sizeof(struct cb_sequence_ref_list),
        (xdrproc_t)op_cb_sequence_ref_list);
    if (!result) { CBX_ERR("sequence_args.ref_lists"); goto out; }
out:
    return result;
}