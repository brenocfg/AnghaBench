#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  xdrproc_t ;
struct TYPE_4__ {scalar_t__ length; int /*<<< orphan*/ * value; } ;
struct TYPE_3__ {int /*<<< orphan*/  gc_ctx; int /*<<< orphan*/  gc_proc; } ;
struct rpc_sspi_data {scalar_t__ established; TYPE_2__ gc_wire_verf; int /*<<< orphan*/  ctx; TYPE_1__ gc; int /*<<< orphan*/  clnt; } ;
typedef  int /*<<< orphan*/  AUTH ;

/* Variables and functions */
 struct rpc_sspi_data* AUTH_PRIVATE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  AUTH_TIMEOUT ; 
 int /*<<< orphan*/  DeleteSecurityContext (int /*<<< orphan*/ *) ; 
 scalar_t__ FALSE ; 
 int /*<<< orphan*/  NULLPROC ; 
 int /*<<< orphan*/  RPCSEC_SSPI_DESTROY ; 
 int /*<<< orphan*/  SecInvalidateHandle (int /*<<< orphan*/ *) ; 
 scalar_t__ SecIsValidHandle (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  clnt_call (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gss_delete_sec_context (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gss_release_buffer (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  log_debug (char*) ; 
 int /*<<< orphan*/  mem_free (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  min_stat ; 
 int /*<<< orphan*/  sspi_release_buffer (int /*<<< orphan*/ *) ; 
 scalar_t__ xdr_void ; 

__attribute__((used)) static void
authsspi_destroy_context(AUTH *auth)
{
	struct rpc_sspi_data *gd;

	log_debug("in authgss_destroy_context()");

	gd = AUTH_PRIVATE(auth);
    if (gd == NULL) return;

	if (SecIsValidHandle(&gd->ctx)) {
		if (gd->established) {
			gd->gc.gc_proc = RPCSEC_SSPI_DESTROY;
			clnt_call(gd->clnt, NULLPROC, (xdrproc_t)xdr_void, NULL,
				  (xdrproc_t)xdr_void, NULL, AUTH_TIMEOUT);
            DeleteSecurityContext(&gd->ctx);
		}
        sspi_release_buffer(&gd->gc.gc_ctx);
        SecInvalidateHandle(&gd->ctx);
#if 0
		gss_release_buffer(&min_stat, &gd->gc.gc_ctx);
		/* XXX ANDROS check size of context  - should be 8 */
		memset(&gd->gc.gc_ctx, 0, sizeof(gd->gc.gc_ctx));
		gss_delete_sec_context(&min_stat, &gd->ctx, NULL);
#endif
	}

	/* free saved wire verifier (if any) */
	mem_free(gd->gc_wire_verf.value, gd->gc_wire_verf.length);
	gd->gc_wire_verf.value = NULL;
	gd->gc_wire_verf.length = 0;

	gd->established = FALSE;
}