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
typedef  int /*<<< orphan*/  u_int ;
struct rpc_sspi_data {TYPE_1__* sec; int /*<<< orphan*/  ctx; int /*<<< orphan*/  established; } ;
typedef  int /*<<< orphan*/  caddr_t ;
typedef  int /*<<< orphan*/  bool_t ;
typedef  int /*<<< orphan*/  XDR ;
struct TYPE_2__ {scalar_t__ svc; int /*<<< orphan*/  qop; } ;
typedef  int /*<<< orphan*/  AUTH ;

/* Variables and functions */
 struct rpc_sspi_data* AUTH_PRIVATE (int /*<<< orphan*/ *) ; 
 scalar_t__ RPCSEC_SSPI_SVC_NONE ; 
 int /*<<< orphan*/  log_debug (char*) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xdr_rpc_sspi_data (int /*<<< orphan*/ *,int /*<<< orphan*/  (*) (int /*<<< orphan*/ *,int /*<<< orphan*/ ),int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 

bool_t
authsspi_unwrap(AUTH *auth, XDR *xdrs, xdrproc_t xdr_func, caddr_t xdr_ptr, u_int seq)
{
	struct rpc_sspi_data	*gd;

	log_debug("in authgss_unwrap()");

	gd = AUTH_PRIVATE(auth);

	if (!gd->established || gd->sec->svc == RPCSEC_SSPI_SVC_NONE) {
		return ((*xdr_func)(xdrs, xdr_ptr));
	}
	return (xdr_rpc_sspi_data(xdrs, xdr_func, xdr_ptr,
				 &gd->ctx, gd->sec->qop,
				 gd->sec->svc, seq));
}