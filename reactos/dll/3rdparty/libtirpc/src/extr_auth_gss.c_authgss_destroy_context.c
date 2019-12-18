#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  xdrproc_t ;
struct TYPE_6__ {scalar_t__ length; int /*<<< orphan*/ * value; } ;
struct TYPE_7__ {scalar_t__ length; } ;
struct TYPE_5__ {TYPE_3__ gc_ctx; int /*<<< orphan*/  gc_proc; } ;
struct rpc_gss_data {scalar_t__ ctx; scalar_t__ established; TYPE_2__ gc_wire_verf; TYPE_1__ gc; int /*<<< orphan*/  clnt; } ;
typedef  int /*<<< orphan*/  OM_uint32 ;
typedef  int /*<<< orphan*/  AUTH ;

/* Variables and functions */
 struct rpc_gss_data* AUTH_PRIVATE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  AUTH_TIMEOUT ; 
 scalar_t__ FALSE ; 
 scalar_t__ GSS_C_NO_CONTEXT ; 
 int /*<<< orphan*/  NULLPROC ; 
 int /*<<< orphan*/  RPCSEC_GSS_DESTROY ; 
 int /*<<< orphan*/  clnt_call (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gss_delete_sec_context (int /*<<< orphan*/ *,scalar_t__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gss_release_buffer (int /*<<< orphan*/ *,TYPE_3__*) ; 
 int /*<<< orphan*/  log_debug (char*) ; 
 int /*<<< orphan*/  mem_free (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  memset (TYPE_3__*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ xdr_void ; 

__attribute__((used)) static void
authgss_destroy_context(AUTH *auth)
{
	struct rpc_gss_data	*gd;
	OM_uint32		 min_stat;

	log_debug("in authgss_destroy_context()");

	gd = AUTH_PRIVATE(auth);

	if (gd->gc.gc_ctx.length != 0) {
		if (gd->established) {
			gd->gc.gc_proc = RPCSEC_GSS_DESTROY;
			clnt_call(gd->clnt, NULLPROC, (xdrproc_t)xdr_void, NULL,
				  (xdrproc_t)xdr_void, NULL, AUTH_TIMEOUT);
		}
		gss_release_buffer(&min_stat, &gd->gc.gc_ctx);
		/* XXX ANDROS check size of context  - should be 8 */
		memset(&gd->gc.gc_ctx, 0, sizeof(gd->gc.gc_ctx));
	}
	if (gd->ctx != GSS_C_NO_CONTEXT) {
		gss_delete_sec_context(&min_stat, &gd->ctx, NULL);
		gd->ctx = GSS_C_NO_CONTEXT;
	}

	/* free saved wire verifier (if any) */
	mem_free(gd->gc_wire_verf.value, gd->gc_wire_verf.length);
	gd->gc_wire_verf.value = NULL;
	gd->gc_wire_verf.length = 0;

	gd->established = FALSE;
}