#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  linebuf ;
struct TYPE_2__ {unsigned long start; unsigned long end; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int E2BIG ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  dprintf4 (char*,int,unsigned long,unsigned long,char*) ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fdopen (int,char*) ; 
 scalar_t__ feof (int /*<<< orphan*/ *) ; 
 char* fgets (char*,int,int /*<<< orphan*/ *) ; 
 int last_range ; 
 int /*<<< orphan*/  mpx_dig_abort () ; 
 size_t nr_ranges_allocated ; 
 size_t nr_ranges_populated ; 
 int open_proc (int,char*) ; 
 TYPE_1__* ranges ; 
 int sscanf (char*,char*,unsigned long*,unsigned long*,char*) ; 

int __pid_load_vaddrs(int pid)
{
	int ret = 0;
	int proc_maps_fd = open_proc(pid, "maps");
	char linebuf[10000];
	unsigned long start;
	unsigned long end;
	char rest[1000];
	FILE *f = fdopen(proc_maps_fd, "r");

	if (!f)
		mpx_dig_abort();
	nr_ranges_populated = 0;
	while (!feof(f)) {
		char *readret = fgets(linebuf, sizeof(linebuf), f);
		int parsed;

		if (readret == NULL) {
			if (feof(f))
				break;
			mpx_dig_abort();
		}

		parsed = sscanf(linebuf, "%lx-%lx%s", &start, &end, rest);
		if (parsed != 3)
			mpx_dig_abort();

		dprintf4("result[%d]: %lx-%lx<->%s\n", parsed, start, end, rest);
		if (nr_ranges_populated >= nr_ranges_allocated) {
			ret = -E2BIG;
			break;
		}
		ranges[nr_ranges_populated].start = start;
		ranges[nr_ranges_populated].end = end;
		nr_ranges_populated++;
	}
	last_range = -1;
	fclose(f);
	close(proc_maps_fd);
	return ret;
}