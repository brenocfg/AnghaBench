#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct svc_rpc_gss_data {scalar_t__ client_name; int /*<<< orphan*/  cname; int /*<<< orphan*/  ctx; } ;
typedef  int /*<<< orphan*/  bool_t ;
typedef  struct svc_rpc_gss_data SVCAUTH ;
typedef  int /*<<< orphan*/  OM_uint32 ;

/* Variables and functions */
 int /*<<< orphan*/  GSS_C_NO_BUFFER ; 
 struct svc_rpc_gss_data* SVCAUTH_PRIVATE (struct svc_rpc_gss_data*) ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  gss_delete_sec_context (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gss_release_buffer (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gss_release_name (int /*<<< orphan*/ *,scalar_t__*) ; 
 int /*<<< orphan*/  log_debug (char*) ; 
 int /*<<< orphan*/  mem_free (struct svc_rpc_gss_data*,int) ; 

bool_t
svcauth_gss_destroy(SVCAUTH *auth)
{
	struct svc_rpc_gss_data	*gd;
	OM_uint32		 min_stat;

	log_debug("in svcauth_gss_destroy()");

	gd = SVCAUTH_PRIVATE(auth);

	gss_delete_sec_context(&min_stat, &gd->ctx, GSS_C_NO_BUFFER);
	gss_release_buffer(&min_stat, &gd->cname);

	if (gd->client_name)
		gss_release_name(&min_stat, &gd->client_name);

	mem_free(gd, sizeof(*gd));
	mem_free(auth, sizeof(*auth));

	return (TRUE);
}