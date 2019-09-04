#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {unsigned long first; unsigned long last; } ;
struct TYPE_3__ {unsigned long first; unsigned long last; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char*,char*) ; 
 int fscanf (int /*<<< orphan*/ *,char*,unsigned long*,unsigned long*,char*,char*) ; 
 TYPE_2__ libc ; 
 int /*<<< orphan*/  perror (char*) ; 
 scalar_t__ strstr (char*,char*) ; 
 TYPE_1__ vdso ; 

int parse_proc_maps(void)
{
	unsigned long start, end;
	char execute, name[128];
	FILE *f;
	int rc;

	f = fopen("/proc/self/maps", "r");
	if (!f) {
		perror("fopen");
		return -1;
	}

	do {
		/* This skips line with no executable which is what we want */
		rc = fscanf(f, "%lx-%lx %*c%*c%c%*c %*x %*d:%*d %*d %127s\n",
			    &start, &end, &execute, name);
		if (rc <= 0)
			break;

		if (execute != 'x')
			continue;

		if (strstr(name, "libc")) {
			libc.first = start;
			libc.last = end - 1;
		} else if (strstr(name, "[vdso]")) {
			vdso.first = start;
			vdso.last = end - 1;
		}
	} while(1);

	fclose(f);

	return 0;
}