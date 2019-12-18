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
typedef  int /*<<< orphan*/  (* JitProviderInit ) (int /*<<< orphan*/ *) ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUG1 ; 
 int /*<<< orphan*/  DLSUFFIX ; 
 int MAXPGPATH ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  file_exists (char*) ; 
 int /*<<< orphan*/  jit_enabled ; 
 char* jit_provider ; 
 scalar_t__ load_external_function (char*,char*,int,int /*<<< orphan*/ *) ; 
 char* pkglib_path ; 
 int /*<<< orphan*/  provider ; 
 int provider_failed_loading ; 
 int provider_successfully_loaded ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char*,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool
provider_init(void)
{
	char		path[MAXPGPATH];
	JitProviderInit init;

	/* don't even try to load if not enabled */
	if (!jit_enabled)
		return false;

	/*
	 * Don't retry loading after failing - attempting to load JIT provider
	 * isn't cheap.
	 */
	if (provider_failed_loading)
		return false;
	if (provider_successfully_loaded)
		return true;

	/*
	 * Check whether shared library exists. We do that check before actually
	 * attempting to load the shared library (via load_external_function()),
	 * because that'd error out in case the shlib isn't available.
	 */
	snprintf(path, MAXPGPATH, "%s/%s%s", pkglib_path, jit_provider, DLSUFFIX);
	elog(DEBUG1, "probing availability of JIT provider at %s", path);
	if (!file_exists(path))
	{
		elog(DEBUG1,
			 "provider not available, disabling JIT for current session");
		provider_failed_loading = true;
		return false;
	}

	/*
	 * If loading functions fails, signal failure. We do so because
	 * load_external_function() might error out despite the above check if
	 * e.g. the library's dependencies aren't installed. We want to signal
	 * ERROR in that case, so the user is notified, but we don't want to
	 * continually retry.
	 */
	provider_failed_loading = true;

	/* and initialize */
	init = (JitProviderInit)
		load_external_function(path, "_PG_jit_provider_init", true, NULL);
	init(&provider);

	provider_successfully_loaded = true;
	provider_failed_loading = false;

	elog(DEBUG1, "successfully loaded JIT provider in current session");

	return true;
}