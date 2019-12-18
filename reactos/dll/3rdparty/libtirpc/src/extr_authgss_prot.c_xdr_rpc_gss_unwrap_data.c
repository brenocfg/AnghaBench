#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ (* xdrproc_t ) (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ;
typedef  int /*<<< orphan*/  wrapbuf ;
typedef  scalar_t__ u_int ;
typedef  scalar_t__ rpc_gss_svc_t ;
typedef  scalar_t__ gss_qop_t ;
typedef  int /*<<< orphan*/  gss_ctx_id_t ;
struct TYPE_8__ {int /*<<< orphan*/  length; int /*<<< orphan*/  value; } ;
typedef  TYPE_1__ gss_buffer_desc ;
typedef  int /*<<< orphan*/  databuf ;
typedef  int /*<<< orphan*/ * caddr_t ;
typedef  int bool_t ;
typedef  int /*<<< orphan*/  XDR ;
typedef  scalar_t__ OM_uint32 ;

/* Variables and functions */
 int FALSE ; 
 scalar_t__ GSS_S_COMPLETE ; 
 int /*<<< orphan*/  MAX_NETOBJ_SZ ; 
 scalar_t__ RPCSEC_GSS_SVC_INTEGRITY ; 
 scalar_t__ RPCSEC_GSS_SVC_PRIVACY ; 
 int TRUE ; 
 int /*<<< orphan*/  XDR_DECODE ; 
 int /*<<< orphan*/  XDR_DESTROY (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gss_release_buffer (scalar_t__*,TYPE_1__*) ; 
 scalar_t__ gss_unwrap (scalar_t__*,int /*<<< orphan*/ ,TYPE_1__*,TYPE_1__*,int*,scalar_t__*) ; 
 scalar_t__ gss_verify_mic (scalar_t__*,int /*<<< orphan*/ ,TYPE_1__*,TYPE_1__*,scalar_t__*) ; 
 int /*<<< orphan*/  log_debug (char*) ; 
 int /*<<< orphan*/  log_status (char*,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ stub1 (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xdr_bytes (int /*<<< orphan*/ *,char**,scalar_t__*,int /*<<< orphan*/ ) ; 
 scalar_t__ xdr_u_int (int /*<<< orphan*/ *,scalar_t__*) ; 
 scalar_t__ xdr_void ; 
 int /*<<< orphan*/  xdrmem_create (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

bool_t
xdr_rpc_gss_unwrap_data(XDR *xdrs, xdrproc_t xdr_func, caddr_t xdr_ptr,
			gss_ctx_id_t ctx, gss_qop_t qop,
			rpc_gss_svc_t svc, u_int seq)
{
	XDR		tmpxdrs;
	gss_buffer_desc	databuf, wrapbuf;
	OM_uint32	maj_stat, min_stat;
	u_int		seq_num, qop_state;
	int			conf_state;
	bool_t		xdr_stat;

	if (xdr_func == (xdrproc_t)xdr_void || xdr_ptr == NULL)
		return (TRUE);

	memset(&databuf, 0, sizeof(databuf));
	memset(&wrapbuf, 0, sizeof(wrapbuf));

	if (svc == RPCSEC_GSS_SVC_INTEGRITY) {
		/* Decode databody_integ. */
		if (!xdr_bytes(xdrs, (char **)&databuf.value, (u_int *)&databuf.length,
			       MAX_NETOBJ_SZ)) {
			log_debug("xdr decode databody_integ failed");
			return (FALSE);
		}
		/* Decode checksum. */
		if (!xdr_bytes(xdrs, (char **)&wrapbuf.value, (u_int *)&wrapbuf.length,
			       MAX_NETOBJ_SZ)) {
			gss_release_buffer(&min_stat, &databuf);
			log_debug("xdr decode checksum failed");
			return (FALSE);
		}
		/* Verify checksum and QOP. */
		maj_stat = gss_verify_mic(&min_stat, ctx, &databuf,
					  &wrapbuf, &qop_state);
		gss_release_buffer(&min_stat, &wrapbuf);

		if (maj_stat != GSS_S_COMPLETE || qop_state != qop) {
			gss_release_buffer(&min_stat, &databuf);
			log_status("gss_verify_mic", maj_stat, min_stat);
			return (FALSE);
		}
	}
	else if (svc == RPCSEC_GSS_SVC_PRIVACY) {
		/* Decode databody_priv. */
		if (!xdr_bytes(xdrs, (char **)&wrapbuf.value, (u_int *)&wrapbuf.length,
			       MAX_NETOBJ_SZ)) {
			log_debug("xdr decode databody_priv failed");
			return (FALSE);
		}
		/* Decrypt databody. */
		maj_stat = gss_unwrap(&min_stat, ctx, &wrapbuf, &databuf,
				      &conf_state, &qop_state);

		gss_release_buffer(&min_stat, &wrapbuf);

		/* Verify encryption and QOP. */
		if (maj_stat != GSS_S_COMPLETE || qop_state != qop ||
			conf_state != TRUE) {
			gss_release_buffer(&min_stat, &databuf);
			log_status("gss_unwrap", maj_stat, min_stat);
			return (FALSE);
		}
	}
	/* Decode rpc_gss_data_t (sequence number + arguments). */
	xdrmem_create(&tmpxdrs, databuf.value, databuf.length, XDR_DECODE);
	xdr_stat = (xdr_u_int(&tmpxdrs, &seq_num) &&
		    (*xdr_func)(&tmpxdrs, xdr_ptr));
	XDR_DESTROY(&tmpxdrs);
	gss_release_buffer(&min_stat, &databuf);

	/* Verify sequence number. */
	if (xdr_stat == TRUE && seq_num != seq) {
		log_debug("wrong sequence number in databody");
		return (FALSE);
	}
	return (xdr_stat);
}