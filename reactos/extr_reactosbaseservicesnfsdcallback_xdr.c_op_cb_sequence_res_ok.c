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
struct cb_sequence_res_ok {int /*<<< orphan*/  target_highest_slotid; int /*<<< orphan*/  highest_slotid; int /*<<< orphan*/  slotid; int /*<<< orphan*/  sequenceid; int /*<<< orphan*/  sessionid; } ;
typedef  scalar_t__ bool_t ;
typedef  int /*<<< orphan*/  XDR ;

/* Variables and functions */
 int /*<<< orphan*/  CBX_ERR (char*) ; 
 int /*<<< orphan*/  NFS4_SESSIONID_SIZE ; 
 scalar_t__ xdr_opaque (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ xdr_u_int32_t (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static bool_t op_cb_sequence_res_ok(XDR *xdr, struct cb_sequence_res_ok *res)
{
    bool_t result;

    result = xdr_opaque(xdr, res->sessionid, NFS4_SESSIONID_SIZE);
    if (!result) { CBX_ERR("sequence_res.sessionid"); goto out; }

    result = xdr_u_int32_t(xdr, &res->sequenceid);
    if (!result) { CBX_ERR("sequence_res.sequenceid"); goto out; }

    result = xdr_u_int32_t(xdr, &res->slotid);
    if (!result) { CBX_ERR("sequence_res.slotid"); goto out; }

    result = xdr_u_int32_t(xdr, &res->highest_slotid);
    if (!result) { CBX_ERR("sequence_res.highest_slotid"); goto out; }

    result = xdr_u_int32_t(xdr, &res->target_highest_slotid);
    if (!result) { CBX_ERR("sequence_res.target_highest_slotid"); goto out; }
out:
    return result;
}