#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  (* xdrproc_t ) (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ;
struct TYPE_2__ {scalar_t__ svc; int /*<<< orphan*/  qop; } ;
struct svc_rpc_gss_data {int /*<<< orphan*/  seq; TYPE_1__ sec; int /*<<< orphan*/  ctx; int /*<<< orphan*/  established; } ;
typedef  int /*<<< orphan*/  caddr_t ;
typedef  int /*<<< orphan*/  bool_t ;
typedef  int /*<<< orphan*/  XDR ;
typedef  int /*<<< orphan*/  SVCAUTH ;

/* Variables and functions */
 scalar_t__ RPCSEC_GSS_SVC_NONE ; 
 struct svc_rpc_gss_data* SVCAUTH_PRIVATE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  log_debug (char*) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xdr_rpc_gss_data (int /*<<< orphan*/ *,int /*<<< orphan*/  (*) (int /*<<< orphan*/ *,int /*<<< orphan*/ ),int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 

bool_t
svcauth_gss_unwrap(SVCAUTH *auth, XDR *xdrs, xdrproc_t xdr_func, caddr_t xdr_ptr)
{
	struct svc_rpc_gss_data	*gd;

	log_debug("in svcauth_gss_unwrap()");

	gd = SVCAUTH_PRIVATE(auth);

	if (!gd->established || gd->sec.svc == RPCSEC_GSS_SVC_NONE) {
		return ((*xdr_func)(xdrs, xdr_ptr));
	}
	return (xdr_rpc_gss_data(xdrs, xdr_func, xdr_ptr,
				 gd->ctx, gd->sec.qop,
				 gd->sec.svc, gd->seq));
}