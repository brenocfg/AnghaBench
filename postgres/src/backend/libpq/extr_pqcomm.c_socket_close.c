#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {scalar_t__ ctx; scalar_t__ cred; } ;
struct TYPE_4__ {int /*<<< orphan*/  sock; TYPE_2__* gss; } ;
typedef  int /*<<< orphan*/  OM_uint32 ;
typedef  int /*<<< orphan*/  Datum ;

/* Variables and functions */
 scalar_t__ GSS_C_NO_CONTEXT ; 
 scalar_t__ GSS_C_NO_CREDENTIAL ; 
 TYPE_1__* MyProcPort ; 
 int /*<<< orphan*/  PGINVALID_SOCKET ; 
 int /*<<< orphan*/  free (TYPE_2__*) ; 
 int /*<<< orphan*/  gss_delete_sec_context (int /*<<< orphan*/ *,scalar_t__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gss_release_cred (int /*<<< orphan*/ *,scalar_t__*) ; 
 int /*<<< orphan*/  secure_close (TYPE_1__*) ; 

__attribute__((used)) static void
socket_close(int code, Datum arg)
{
	/* Nothing to do in a standalone backend, where MyProcPort is NULL. */
	if (MyProcPort != NULL)
	{
#if defined(ENABLE_GSS) || defined(ENABLE_SSPI)
#ifdef ENABLE_GSS
		OM_uint32	min_s;

		/*
		 * Shutdown GSSAPI layer.  This section does nothing when interrupting
		 * BackendInitialize(), because pg_GSS_recvauth() makes first use of
		 * "ctx" and "cred".
		 */
		if (MyProcPort->gss->ctx != GSS_C_NO_CONTEXT)
			gss_delete_sec_context(&min_s, &MyProcPort->gss->ctx, NULL);

		if (MyProcPort->gss->cred != GSS_C_NO_CREDENTIAL)
			gss_release_cred(&min_s, &MyProcPort->gss->cred);
#endif							/* ENABLE_GSS */

		/*
		 * GSS and SSPI share the port->gss struct.  Since nowhere else does a
		 * postmaster child free this, doing so is safe when interrupting
		 * BackendInitialize().
		 */
		free(MyProcPort->gss);
#endif							/* ENABLE_GSS || ENABLE_SSPI */

		/*
		 * Cleanly shut down SSL layer.  Nowhere else does a postmaster child
		 * call this, so this is safe when interrupting BackendInitialize().
		 */
		secure_close(MyProcPort);

		/*
		 * Formerly we did an explicit close() here, but it seems better to
		 * leave the socket open until the process dies.  This allows clients
		 * to perform a "synchronous close" if they care --- wait till the
		 * transport layer reports connection closure, and you can be sure the
		 * backend has exited.
		 *
		 * We do set sock to PGINVALID_SOCKET to prevent any further I/O,
		 * though.
		 */
		MyProcPort->sock = PGINVALID_SOCKET;
	}
}