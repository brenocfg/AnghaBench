#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_5__ ;
typedef  struct TYPE_16__   TYPE_4__ ;
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  tmp ;
struct TYPE_13__ {int /*<<< orphan*/  qop; } ;
struct TYPE_16__ {scalar_t__ gc_proc; int /*<<< orphan*/  gc_seq; } ;
struct rpc_gss_data {scalar_t__ established; TYPE_1__ sec; int /*<<< orphan*/  ctx; TYPE_4__ gc; } ;
struct TYPE_14__ {char* value; void* length; } ;
typedef  TYPE_2__ gss_buffer_desc ;
typedef  scalar_t__ bool_t ;
typedef  int /*<<< orphan*/  XDR ;
struct TYPE_17__ {char* oa_base; void* oa_length; void* oa_flavor; } ;
struct TYPE_15__ {TYPE_5__ ah_verf; TYPE_5__ ah_cred; } ;
typedef  scalar_t__ OM_uint32 ;
typedef  TYPE_3__ AUTH ;

/* Variables and functions */
 struct rpc_gss_data* AUTH_PRIVATE (TYPE_3__*) ; 
 scalar_t__ FALSE ; 
 scalar_t__ GSS_S_COMPLETE ; 
 scalar_t__ GSS_S_CONTEXT_EXPIRED ; 
 int MAX_AUTH_BYTES ; 
 void* RPCSEC_GSS ; 
 scalar_t__ RPCSEC_GSS_CONTINUE_INIT ; 
 scalar_t__ RPCSEC_GSS_INIT ; 
 int /*<<< orphan*/  XDR_DESTROY (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  XDR_ENCODE ; 
 void* XDR_GETPOS (int /*<<< orphan*/ *) ; 
 char* XDR_INLINE (int /*<<< orphan*/ *,void*) ; 
 int /*<<< orphan*/  XDR_SETPOS (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 TYPE_5__ _null_auth ; 
 int /*<<< orphan*/  authgss_destroy_context (TYPE_3__*) ; 
 scalar_t__ gss_get_mic (scalar_t__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_2__*,TYPE_2__*) ; 
 int /*<<< orphan*/  gss_release_buffer (scalar_t__*,TYPE_2__*) ; 
 int /*<<< orphan*/  log_debug (char*) ; 
 int /*<<< orphan*/  log_status (char*,scalar_t__,scalar_t__) ; 
 scalar_t__ xdr_opaque_auth (int /*<<< orphan*/ *,TYPE_5__*) ; 
 int /*<<< orphan*/  xdr_rpc_gss_cred (int /*<<< orphan*/ *,TYPE_4__*) ; 
 int /*<<< orphan*/  xdrmem_create (int /*<<< orphan*/ *,char*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool_t
authgss_marshal(AUTH *auth, XDR *xdrs)
{
	XDR			 tmpxdrs;
	char			 tmp[MAX_AUTH_BYTES];
	struct rpc_gss_data	*gd;
	gss_buffer_desc		 rpcbuf, checksum;
	OM_uint32		 maj_stat, min_stat;
	bool_t			 xdr_stat;

	log_debug("in authgss_marshal()");

	gd = AUTH_PRIVATE(auth);

	if (gd->established)
		gd->gc.gc_seq++;

	xdrmem_create(&tmpxdrs, tmp, sizeof(tmp), XDR_ENCODE);

	if (!xdr_rpc_gss_cred(&tmpxdrs, &gd->gc)) {
		XDR_DESTROY(&tmpxdrs);
		return (FALSE);
	}
	auth->ah_cred.oa_flavor = RPCSEC_GSS;
	auth->ah_cred.oa_base = tmp;
	auth->ah_cred.oa_length = XDR_GETPOS(&tmpxdrs);

	XDR_DESTROY(&tmpxdrs);

	if (!xdr_opaque_auth(xdrs, &auth->ah_cred))
		return (FALSE);

	if (gd->gc.gc_proc == RPCSEC_GSS_INIT ||
	    gd->gc.gc_proc == RPCSEC_GSS_CONTINUE_INIT) {
		return (xdr_opaque_auth(xdrs, &_null_auth));
	}
	/* Checksum serialized RPC header, up to and including credential. */
	rpcbuf.length = XDR_GETPOS(xdrs);
	XDR_SETPOS(xdrs, 0);
	rpcbuf.value = XDR_INLINE(xdrs, rpcbuf.length);

	maj_stat = gss_get_mic(&min_stat, gd->ctx, gd->sec.qop,
			    &rpcbuf, &checksum);

	if (maj_stat != GSS_S_COMPLETE) {
		log_status("gss_get_mic", maj_stat, min_stat);
		if (maj_stat == GSS_S_CONTEXT_EXPIRED) {
			gd->established = FALSE;
			authgss_destroy_context(auth);
		}
		return (FALSE);
	}
	auth->ah_verf.oa_flavor = RPCSEC_GSS;
	auth->ah_verf.oa_base = checksum.value;
	auth->ah_verf.oa_length = checksum.length;

	xdr_stat = xdr_opaque_auth(xdrs, &auth->ah_verf);
	gss_release_buffer(&min_stat, &checksum);

	return (xdr_stat);
}