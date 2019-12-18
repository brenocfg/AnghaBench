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
struct rpc_gss_data {scalar_t__ name; } ;
typedef  int /*<<< orphan*/  OM_uint32 ;
typedef  struct rpc_gss_data AUTH ;

/* Variables and functions */
 struct rpc_gss_data* AUTH_PRIVATE (struct rpc_gss_data*) ; 
 scalar_t__ GSS_C_NO_NAME ; 
 int /*<<< orphan*/  authgss_destroy_context (struct rpc_gss_data*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,scalar_t__) ; 
 int /*<<< orphan*/  free (struct rpc_gss_data*) ; 
 int /*<<< orphan*/  gss_release_name (int /*<<< orphan*/ *,scalar_t__*) ; 
 int /*<<< orphan*/  log_debug (char*) ; 
 int /*<<< orphan*/  stderr ; 

__attribute__((used)) static void
authgss_destroy(AUTH *auth)
{
	struct rpc_gss_data	*gd;
	OM_uint32		 min_stat;

	log_debug("in authgss_destroy()");

	gd = AUTH_PRIVATE(auth);

	authgss_destroy_context(auth);

#ifdef DEBUG
	fprintf(stderr, "authgss_destroy: freeing name %p\n", gd->name);
#endif
	if (gd->name != GSS_C_NO_NAME)
		gss_release_name(&min_stat, &gd->name);

	free(gd);
	free(auth);
}