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
struct dstr {char* array; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  _SC_NPROCESSORS_ONLN ; 
 int atoi (char*) ; 
 int /*<<< orphan*/  bfree (char*) ; 
 int core_count_initialized ; 
 int /*<<< orphan*/  dstr_cat (struct dstr*,char*) ; 
 int /*<<< orphan*/  dstr_cat_dstr (struct dstr*,struct dstr*) ; 
 int /*<<< orphan*/  dstr_catf (struct dstr*,char*,int) ; 
 int /*<<< orphan*/  dstr_find (struct dstr*,char*) ; 
 int /*<<< orphan*/  dstr_free (struct dstr*) ; 
 int /*<<< orphan*/  dstr_init (struct dstr*) ; 
 scalar_t__ dstr_is_empty (struct dstr*) ; 
 int /*<<< orphan*/  dstr_ncopy (struct dstr*,char*,size_t) ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char*,char*) ; 
 int /*<<< orphan*/  free (char*) ; 
 int getline (char**,size_t*,int /*<<< orphan*/ *) ; 
 int logical_cores ; 
 char* os_quick_read_utf8_file (char*) ; 
 int physical_cores ; 
 char* strchr (char*,char) ; 
 size_t strcspn (char*,char*) ; 
 int /*<<< orphan*/  strncmp (char*,char*,int) ; 
 char* strstr (char*,char*) ; 
 int sysconf (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void os_get_cores_internal(void)
{
	if (core_count_initialized)
		return;

	core_count_initialized = true;

	logical_cores = sysconf(_SC_NPROCESSORS_ONLN);

#if defined(__linux__)
	int physical_id = -1;
	int last_physical_id = -1;
	int core_count = 0;
	char *line = NULL;
	size_t linecap = 0;

	FILE *fp;
	struct dstr proc_phys_id;
	struct dstr proc_phys_ids;

	fp = fopen("/proc/cpuinfo", "r");
	if (!fp)
		return;

	dstr_init(&proc_phys_id);
	dstr_init(&proc_phys_ids);

	while (getline(&line, &linecap, fp) != -1) {
		if (!strncmp(line, "physical id", 11)) {
			char *start = strchr(line, ':');
			if (!start || *(++start) == '\0')
				continue;

			physical_id = atoi(start);
			dstr_free(&proc_phys_id);
			dstr_init(&proc_phys_id);
			dstr_catf(&proc_phys_id, "%d", physical_id);
		}

		if (!strncmp(line, "cpu cores", 9)) {
			char *start = strchr(line, ':');
			if (!start || *(++start) == '\0')
				continue;

			if (dstr_is_empty(&proc_phys_ids) ||
			    (!dstr_is_empty(&proc_phys_ids) &&
			     !dstr_find(&proc_phys_ids, proc_phys_id.array))) {
				dstr_cat_dstr(&proc_phys_ids, &proc_phys_id);
				dstr_cat(&proc_phys_ids, " ");
				core_count += atoi(start);
			}
		}

		if (*line == '\n' && physical_id != last_physical_id) {
			last_physical_id = physical_id;
		}
	}

	if (core_count == 0)
		physical_cores = logical_cores;
	else
		physical_cores = core_count;

	fclose(fp);
	dstr_free(&proc_phys_ids);
	dstr_free(&proc_phys_id);
	free(line);
#elif defined(__FreeBSD__)
	char *text = os_quick_read_utf8_file("/var/run/dmesg.boot");
	char *core_count = text;
	int packages = 0;
	int cores = 0;

	struct dstr proc_packages;
	struct dstr proc_cores;
	dstr_init(&proc_packages);
	dstr_init(&proc_cores);

	if (!text || !*text) {
		physical_cores = logical_cores;
		return;
	}

	core_count = strstr(core_count, "\nFreeBSD/SMP: ");
	if (!core_count)
		goto FreeBSD_cores_cleanup;

	core_count++;
	core_count = strstr(core_count, "\nFreeBSD/SMP: ");
	if (!core_count)
		goto FreeBSD_cores_cleanup;

	core_count = strstr(core_count, ": ");
	core_count += 2;
	size_t len = strcspn(core_count, " ");
	dstr_ncopy(&proc_packages, core_count, len);

	core_count = strstr(core_count, "package(s) x ");
	if (!core_count)
		goto FreeBSD_cores_cleanup;

	core_count += 13;
	len = strcspn(core_count, " ");
	dstr_ncopy(&proc_cores, core_count, len);

FreeBSD_cores_cleanup:
	if (!dstr_is_empty(&proc_packages))
		packages = atoi(proc_packages.array);
	if (!dstr_is_empty(&proc_cores))
		cores = atoi(proc_cores.array);

	if (packages == 0)
		physical_cores = logical_cores;
	else if (cores == 0)
		physical_cores = packages;
	else
		physical_cores = packages * cores;

	dstr_free(&proc_cores);
	dstr_free(&proc_packages);
	bfree(text);
#else
	physical_cores = logical_cores;
#endif
}