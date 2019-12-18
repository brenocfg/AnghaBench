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
typedef  int /*<<< orphan*/  u_int ;
struct TYPE_8__ {int /*<<< orphan*/  length; int /*<<< orphan*/  value; } ;
struct TYPE_7__ {int /*<<< orphan*/  length; int /*<<< orphan*/  value; } ;
struct rpc_gss_init_res {TYPE_2__ gr_token; int /*<<< orphan*/  gr_win; int /*<<< orphan*/  gr_minor; int /*<<< orphan*/  gr_major; TYPE_1__ gr_ctx; } ;
typedef  int bool_t ;
struct TYPE_9__ {scalar_t__ x_op; } ;
typedef  TYPE_3__ XDR ;

/* Variables and functions */
 int /*<<< orphan*/  MAX_NETOBJ_SZ ; 
 int TRUE ; 
 scalar_t__ XDR_ENCODE ; 
 int /*<<< orphan*/  log_debug (char*,char*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ xdr_bytes (TYPE_3__*,char**,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ xdr_u_int (TYPE_3__*,int /*<<< orphan*/ *) ; 

bool_t
xdr_rpc_gss_init_res(XDR *xdrs, struct rpc_gss_init_res *p)
{
	bool_t xdr_stat;

	xdr_stat = (xdr_bytes(xdrs, (char **)&p->gr_ctx.value,
			      (u_int *)&p->gr_ctx.length, MAX_NETOBJ_SZ) &&
		    xdr_u_int(xdrs, &p->gr_major) &&
		    xdr_u_int(xdrs, &p->gr_minor) &&
		    xdr_u_int(xdrs, &p->gr_win) &&
		    xdr_bytes(xdrs, (char **)&p->gr_token.value,
			      (u_int *)&p->gr_token.length, MAX_NETOBJ_SZ));

	log_debug("xdr_rpc_gss_init_res %s %s "
		  "(ctx %p:%d, maj %d, min %d, win %d, token %p:%d)",
		  (xdrs->x_op == XDR_ENCODE) ? "encode" : "decode",
		  (xdr_stat == TRUE) ? "success" : "failure",
		  p->gr_ctx.value, p->gr_ctx.length,
		  p->gr_major, p->gr_minor, p->gr_win,
		  p->gr_token.value, p->gr_token.length);

	return (xdr_stat);
}