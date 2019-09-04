#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  xdrproc_t ;
typedef  int /*<<< orphan*/  u_int ;
typedef  int /*<<< orphan*/  rpc_gss_svc_t ;
typedef  int /*<<< orphan*/  gss_qop_t ;
typedef  int /*<<< orphan*/  gss_ctx_id_t ;
typedef  int /*<<< orphan*/  caddr_t ;
typedef  int /*<<< orphan*/  bool_t ;
struct TYPE_5__ {int x_op; } ;
typedef  TYPE_1__ XDR ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 
#define  XDR_DECODE 130 
#define  XDR_ENCODE 129 
#define  XDR_FREE 128 
 int /*<<< orphan*/  xdr_rpc_gss_unwrap_data (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xdr_rpc_gss_wrap_data (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

bool_t
xdr_rpc_gss_data(XDR *xdrs, xdrproc_t xdr_func, caddr_t xdr_ptr,
		 gss_ctx_id_t ctx, gss_qop_t qop,
		 rpc_gss_svc_t svc, u_int seq)
{
	switch (xdrs->x_op) {

	case XDR_ENCODE:
		return (xdr_rpc_gss_wrap_data(xdrs, xdr_func, xdr_ptr,
					      ctx, qop, svc, seq));
	case XDR_DECODE:
		return (xdr_rpc_gss_unwrap_data(xdrs, xdr_func, xdr_ptr,
						ctx, qop,svc, seq));
	case XDR_FREE:
		return (TRUE);
	}
	return (FALSE);
}