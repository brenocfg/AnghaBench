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
struct rpc_sspi_data {scalar_t__ name; struct rpc_sspi_data* sec; int /*<<< orphan*/  cred; } ;
typedef  struct rpc_sspi_data AUTH ;

/* Variables and functions */
 struct rpc_sspi_data* AUTH_PRIVATE (struct rpc_sspi_data*) ; 
 int /*<<< orphan*/  FreeCredentialsHandle (int /*<<< orphan*/ *) ; 
 scalar_t__ SSPI_C_NO_NAME ; 
 int /*<<< orphan*/  authsspi_destroy_context (struct rpc_sspi_data*) ; 
 int /*<<< orphan*/  free (struct rpc_sspi_data*) ; 
 int /*<<< orphan*/  gss_release_name (int /*<<< orphan*/ *,scalar_t__*) ; 
 int /*<<< orphan*/  log_debug (char*) ; 
 int /*<<< orphan*/  min_stat ; 

__attribute__((used)) static void
authsspi_destroy(AUTH *auth)
{
	struct rpc_sspi_data *gd;

	log_debug("in authgss_destroy()");

	gd = AUTH_PRIVATE(auth);
    if (gd == NULL) return;

	authsspi_destroy_context(auth);

#if 0
    if (gd->name != SSPI_C_NO_NAME)
		gss_release_name(&min_stat, &gd->name);
#else
    free(gd->name);
#endif
    FreeCredentialsHandle(&gd->sec->cred);
    free(gd->sec);
	free(gd);
	free(auth);
}