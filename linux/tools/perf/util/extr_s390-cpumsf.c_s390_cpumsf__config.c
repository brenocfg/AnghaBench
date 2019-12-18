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
struct stat {int /*<<< orphan*/  st_mode; } ;
struct s390_cpumsf {int /*<<< orphan*/ * logdir; } ;

/* Variables and functions */
 int /*<<< orphan*/  S_ISDIR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_err (char*,char const*) ; 
 int stat (int /*<<< orphan*/ *,struct stat*) ; 
 scalar_t__ strcmp (char const*,char*) ; 
 int /*<<< orphan*/ * strdup (char const*) ; 
 int /*<<< orphan*/  zfree (int /*<<< orphan*/ **) ; 

__attribute__((used)) static int s390_cpumsf__config(const char *var, const char *value, void *cb)
{
	struct s390_cpumsf *sf = cb;
	struct stat stbuf;
	int rc;

	if (strcmp(var, "auxtrace.dumpdir"))
		return 0;
	sf->logdir = strdup(value);
	if (sf->logdir == NULL) {
		pr_err("Failed to find auxtrace log directory %s,"
		       " continue with current directory...\n", value);
		return 1;
	}
	rc = stat(sf->logdir, &stbuf);
	if (rc == -1 || !S_ISDIR(stbuf.st_mode)) {
		pr_err("Missing auxtrace log directory %s,"
		       " continue with current directory...\n", value);
		zfree(&sf->logdir);
	}
	return 1;
}