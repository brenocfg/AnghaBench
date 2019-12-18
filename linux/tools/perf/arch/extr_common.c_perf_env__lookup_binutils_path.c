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
struct perf_env {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  F_OK ; 
 scalar_t__ access (char*,int /*<<< orphan*/ ) ; 
 char** arc_triplets ; 
 char** arm64_triplets ; 
 char** arm_triplets ; 
 scalar_t__ asprintf (char**,char*,char const* const,char const*) ; 
 int /*<<< orphan*/  free (char*) ; 
 char* getenv (char*) ; 
 scalar_t__ lookup_path (char*) ; 
 int lookup_triplets (char const* const*,char const*) ; 
 char** mips_triplets ; 
 char const* perf_env__arch (struct perf_env*) ; 
 char** powerpc_triplets ; 
 char** s390_triplets ; 
 char** sh_triplets ; 
 char** sparc_triplets ; 
 int /*<<< orphan*/  strcmp (char const*,char const*) ; 
 int /*<<< orphan*/  ui__error (char*,char const*,...) ; 
 char** x86_triplets ; 
 int /*<<< orphan*/  zfree (char**) ; 

__attribute__((used)) static int perf_env__lookup_binutils_path(struct perf_env *env,
					  const char *name, const char **path)
{
	int idx;
	const char *arch = perf_env__arch(env), *cross_env;
	const char *const *path_list;
	char *buf = NULL;

	/*
	 * We don't need to try to find objdump path for native system.
	 * Just use default binutils path (e.g.: "objdump").
	 */
	if (!strcmp(perf_env__arch(NULL), arch))
		goto out;

	cross_env = getenv("CROSS_COMPILE");
	if (cross_env) {
		if (asprintf(&buf, "%s%s", cross_env, name) < 0)
			goto out_error;
		if (buf[0] == '/') {
			if (access(buf, F_OK) == 0)
				goto out;
			goto out_error;
		}
		if (lookup_path(buf))
			goto out;
		zfree(&buf);
	}

	if (!strcmp(arch, "arc"))
		path_list = arc_triplets;
	else if (!strcmp(arch, "arm"))
		path_list = arm_triplets;
	else if (!strcmp(arch, "arm64"))
		path_list = arm64_triplets;
	else if (!strcmp(arch, "powerpc"))
		path_list = powerpc_triplets;
	else if (!strcmp(arch, "sh"))
		path_list = sh_triplets;
	else if (!strcmp(arch, "s390"))
		path_list = s390_triplets;
	else if (!strcmp(arch, "sparc"))
		path_list = sparc_triplets;
	else if (!strcmp(arch, "x86"))
		path_list = x86_triplets;
	else if (!strcmp(arch, "mips"))
		path_list = mips_triplets;
	else {
		ui__error("binutils for %s not supported.\n", arch);
		goto out_error;
	}

	idx = lookup_triplets(path_list, name);
	if (idx < 0) {
		ui__error("Please install %s for %s.\n"
			  "You can add it to PATH, set CROSS_COMPILE or "
			  "override the default using --%s.\n",
			  name, arch, name);
		goto out_error;
	}

	if (asprintf(&buf, "%s%s", path_list[idx], name) < 0)
		goto out_error;

out:
	*path = buf;
	return 0;
out_error:
	free(buf);
	*path = NULL;
	return -1;
}