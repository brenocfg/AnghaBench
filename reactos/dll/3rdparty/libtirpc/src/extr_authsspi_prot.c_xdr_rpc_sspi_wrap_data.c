#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  (* xdrproc_t ) (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ;
typedef  scalar_t__ uint32_t ;
typedef  int /*<<< orphan*/  u_int ;
typedef  int /*<<< orphan*/  sspi_qop_t ;
struct TYPE_12__ {int length; int /*<<< orphan*/  value; } ;
typedef  TYPE_1__ sspi_buffer_desc ;
typedef  scalar_t__ rpc_sspi_svc_t ;
typedef  int /*<<< orphan*/  caddr_t ;
typedef  int /*<<< orphan*/  bool_t ;
typedef  int /*<<< orphan*/  XDR ;
typedef  int /*<<< orphan*/  PCtxtHandle ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 scalar_t__ RPCSEC_SSPI_SVC_INTEGRITY ; 
 scalar_t__ RPCSEC_SSPI_SVC_PRIVACY ; 
 scalar_t__ SEC_E_OK ; 
 int /*<<< orphan*/  TRUE ; 
 int XDR_GETPOS (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  XDR_INLINE (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  XDR_SETPOS (int /*<<< orphan*/ *,int) ; 
 scalar_t__ gss_get_mic (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*,TYPE_1__*) ; 
 int /*<<< orphan*/  gss_release_buffer (int /*<<< orphan*/ *,TYPE_1__*) ; 
 scalar_t__ gss_wrap (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*,int*,TYPE_1__*) ; 
 int /*<<< orphan*/  log_debug (char*,...) ; 
 int /*<<< orphan*/  min_stat ; 
 scalar_t__ sspi_get_mic (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*,TYPE_1__*) ; 
 int /*<<< orphan*/  sspi_release_buffer (TYPE_1__*) ; 
 scalar_t__ sspi_wrap (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*,TYPE_1__*,int*) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xdr_bytes (int /*<<< orphan*/ *,char**,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xdr_u_int (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

bool_t
xdr_rpc_sspi_wrap_data(XDR *xdrs, xdrproc_t xdr_func, caddr_t xdr_ptr,
		      PCtxtHandle ctx, sspi_qop_t qop,
		      rpc_sspi_svc_t svc, u_int seq)
{
	sspi_buffer_desc databuf, wrapbuf;
	uint32_t maj_stat;
	int start, end, conf_state;
	bool_t xdr_stat;

    log_debug("in xdr_rpc_sspi_wrap_data()");

    /* Skip databody length. */
	start = XDR_GETPOS(xdrs);
	XDR_SETPOS(xdrs, start + 4);

	/* Marshal rpc_gss_data_t (sequence number + arguments). */
	if (!xdr_u_int(xdrs, &seq) || !(*xdr_func)(xdrs, xdr_ptr))
		return (FALSE);
	end = XDR_GETPOS(xdrs);

	/* Set databuf to marshalled rpc_gss_data_t. */
	databuf.length = end - start - 4;
	XDR_SETPOS(xdrs, start + 4);
	databuf.value = XDR_INLINE(xdrs, databuf.length);

	xdr_stat = FALSE;

	if (svc == RPCSEC_SSPI_SVC_INTEGRITY) {
		/* Marshal databody_integ length. */
		XDR_SETPOS(xdrs, start);
		if (!xdr_u_int(xdrs, (u_int *)&databuf.length))
			return (FALSE);

		/* Checksum rpc_gss_data_t. */
#if 0
		maj_stat = gss_get_mic(&min_stat, ctx, qop,
				       &databuf, &wrapbuf);
#else
        maj_stat = sspi_get_mic(ctx, 0, seq, &databuf, &wrapbuf);
#endif
		if (maj_stat != SEC_E_OK) {
			log_debug("xdr_rpc_sspi_wrap_data: sspi_get_mic failed with %x", maj_stat);
			return (FALSE);
		}
		/* Marshal checksum. */
		XDR_SETPOS(xdrs, end);
		xdr_stat = xdr_bytes(xdrs, (char **)&wrapbuf.value,
                            (u_int *)&wrapbuf.length, (u_int)-1);
#if 0
		gss_release_buffer(&min_stat, &wrapbuf);
#else
        sspi_release_buffer(&wrapbuf);
#endif
	}
	else if (svc == RPCSEC_SSPI_SVC_PRIVACY) {
		/* Encrypt rpc_gss_data_t. */
#if 0
		maj_stat = gss_wrap(&min_stat, ctx, TRUE, qop, &databuf,
				    &conf_state, &wrapbuf);
#else
        maj_stat = sspi_wrap(ctx, 0, &databuf, &wrapbuf, &conf_state);
#endif
		if (maj_stat != SEC_E_OK) {
			log_debug("xdr_rpc_sspi_wrap_data: sspi_wrap failed with %x", maj_stat);
			return (FALSE);
		}
		/* Marshal databody_priv. */
		XDR_SETPOS(xdrs, start);
		xdr_stat = xdr_bytes(xdrs, (char **)&wrapbuf.value,
                            (u_int *)&wrapbuf.length, (u_int)-1);
#if 0
		gss_release_buffer(&min_stat, &wrapbuf);
#else
        sspi_release_buffer(&wrapbuf);
#endif
	}
	return (xdr_stat);
}