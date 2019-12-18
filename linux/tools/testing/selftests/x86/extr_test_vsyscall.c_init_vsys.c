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
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int MAPS_LINE_LEN ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 scalar_t__ fgets (char*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char*,char*) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int sscanf (char*,char*,void**,void**,char*,char*,char*) ; 
 scalar_t__ strcmp (char*,char*) ; 
 int vsyscall_map_r ; 
 int vsyscall_map_x ; 

__attribute__((used)) static int init_vsys(void)
{
#ifdef __x86_64__
	int nerrs = 0;
	FILE *maps;
	char line[MAPS_LINE_LEN];
	bool found = false;

	maps = fopen("/proc/self/maps", "r");
	if (!maps) {
		printf("[WARN]\tCould not open /proc/self/maps -- assuming vsyscall is r-x\n");
		vsyscall_map_r = true;
		return 0;
	}

	while (fgets(line, MAPS_LINE_LEN, maps)) {
		char r, x;
		void *start, *end;
		char name[MAPS_LINE_LEN];

		/* sscanf() is safe here as strlen(name) >= strlen(line) */
		if (sscanf(line, "%p-%p %c-%cp %*x %*x:%*x %*u %s",
			   &start, &end, &r, &x, name) != 5)
			continue;

		if (strcmp(name, "[vsyscall]"))
			continue;

		printf("\tvsyscall map: %s", line);

		if (start != (void *)0xffffffffff600000 ||
		    end != (void *)0xffffffffff601000) {
			printf("[FAIL]\taddress range is nonsense\n");
			nerrs++;
		}

		printf("\tvsyscall permissions are %c-%c\n", r, x);
		vsyscall_map_r = (r == 'r');
		vsyscall_map_x = (x == 'x');

		found = true;
		break;
	}

	fclose(maps);

	if (!found) {
		printf("\tno vsyscall map in /proc/self/maps\n");
		vsyscall_map_r = false;
		vsyscall_map_x = false;
	}

	return nerrs;
#else
	return 0;
#endif
}