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
struct stat {scalar_t__ st_ino; } ;
struct nsinfo {int pid; int need_setns; char* mntns_path; void* nstgid; void* tgid; } ;
typedef  void* pid_t ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int PATH_MAX ; 
 int asprintf (char**,char*,int) ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char*,char*) ; 
 int /*<<< orphan*/  free (char*) ; 
 int getline (char**,size_t*,int /*<<< orphan*/ *) ; 
 int snprintf (char*,int,char*,...) ; 
 scalar_t__ stat (char*,struct stat*) ; 
 int /*<<< orphan*/  strrchr (char*,char) ; 
 int /*<<< orphan*/ * strstr (char*,char*) ; 
 scalar_t__ strtol (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 

int nsinfo__init(struct nsinfo *nsi)
{
	char oldns[PATH_MAX];
	char spath[PATH_MAX];
	char *newns = NULL;
	char *statln = NULL;
	struct stat old_stat;
	struct stat new_stat;
	FILE *f = NULL;
	size_t linesz = 0;
	int rv = -1;

	if (snprintf(oldns, PATH_MAX, "/proc/self/ns/mnt") >= PATH_MAX)
		return rv;

	if (asprintf(&newns, "/proc/%d/ns/mnt", nsi->pid) == -1)
		return rv;

	if (stat(oldns, &old_stat) < 0)
		goto out;

	if (stat(newns, &new_stat) < 0)
		goto out;

	/* Check if the mount namespaces differ, if so then indicate that we
	 * want to switch as part of looking up dso/map data.
	 */
	if (old_stat.st_ino != new_stat.st_ino) {
		nsi->need_setns = true;
		nsi->mntns_path = newns;
		newns = NULL;
	}

	/* If we're dealing with a process that is in a different PID namespace,
	 * attempt to work out the innermost tgid for the process.
	 */
	if (snprintf(spath, PATH_MAX, "/proc/%d/status", nsi->pid) >= PATH_MAX)
		goto out;

	f = fopen(spath, "r");
	if (f == NULL)
		goto out;

	while (getline(&statln, &linesz, f) != -1) {
		/* Use tgid if CONFIG_PID_NS is not defined. */
		if (strstr(statln, "Tgid:") != NULL) {
			nsi->tgid = (pid_t)strtol(strrchr(statln, '\t'),
						     NULL, 10);
			nsi->nstgid = nsi->tgid;
		}

		if (strstr(statln, "NStgid:") != NULL) {
			nsi->nstgid = (pid_t)strtol(strrchr(statln, '\t'),
						     NULL, 10);
			break;
		}
	}
	rv = 0;

out:
	if (f != NULL)
		(void) fclose(f);
	free(statln);
	free(newns);
	return rv;
}