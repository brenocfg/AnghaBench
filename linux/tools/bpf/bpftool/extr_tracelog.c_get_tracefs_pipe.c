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
typedef  int /*<<< orphan*/  format ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int ARRAY_SIZE (char const* const*) ; 
 scalar_t__ PATH_MAX ; 
 int /*<<< orphan*/  TRACEFS_MAGIC ; 
 scalar_t__ block_mount ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 scalar_t__ find_tracefs_mnt_single (int /*<<< orphan*/ ,char*,char const* const) ; 
 int /*<<< orphan*/ * fopen (char*,char*) ; 
 int fscanf (int /*<<< orphan*/ *,char*,char*,char*) ; 
 scalar_t__ mount_tracefs (char*) ; 
 int /*<<< orphan*/  p_info (char*) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,scalar_t__) ; 
 int /*<<< orphan*/  strcat (char*,char const*) ; 
 scalar_t__ strcmp (char*,char const*) ; 
 int /*<<< orphan*/  strcpy (char*,char const* const) ; 
 scalar_t__ strlen (char const*) ; 
 scalar_t__ validate_tracefs_mnt (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool get_tracefs_pipe(char *mnt)
{
	static const char * const known_mnts[] = {
		"/sys/kernel/debug/tracing",
		"/sys/kernel/tracing",
		"/tracing",
		"/trace",
	};
	const char *pipe_name = "/trace_pipe";
	const char *fstype = "tracefs";
	char type[100], format[32];
	const char * const *ptr;
	bool found = false;
	FILE *fp;

	for (ptr = known_mnts; ptr < known_mnts + ARRAY_SIZE(known_mnts); ptr++)
		if (find_tracefs_mnt_single(TRACEFS_MAGIC, mnt, *ptr))
			goto exit_found;

	fp = fopen("/proc/mounts", "r");
	if (!fp)
		return false;

	/* Allow room for NULL terminating byte and pipe file name */
	snprintf(format, sizeof(format), "%%*s %%%zds %%99s %%*s %%*d %%*d\\n",
		 PATH_MAX - strlen(pipe_name) - 1);
	while (fscanf(fp, format, mnt, type) == 2)
		if (strcmp(type, fstype) == 0) {
			found = true;
			break;
		}
	fclose(fp);

	/* The string from fscanf() might be truncated, check mnt is valid */
	if (found && validate_tracefs_mnt(mnt, TRACEFS_MAGIC))
		goto exit_found;

	if (block_mount)
		return false;

	p_info("could not find tracefs, attempting to mount it now");
	/* Most of the time, tracefs is automatically mounted by debugfs at
	 * /sys/kernel/debug/tracing when we try to access it. If we could not
	 * find it, it is likely that debugfs is not mounted. Let's give one
	 * attempt at mounting just tracefs at /sys/kernel/tracing.
	 */
	strcpy(mnt, known_mnts[1]);
	if (mount_tracefs(mnt))
		return false;

exit_found:
	strcat(mnt, pipe_name);
	return true;
}