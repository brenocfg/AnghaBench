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

/* Variables and functions */
 int /*<<< orphan*/ * CPU_ALLOC (int) ; 
 scalar_t__ CPU_ISSET_S (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CPU_SET_S (int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  CPU_ZERO_S (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cpu_present_set ; 
 int /*<<< orphan*/ * cpu_selected_set ; 
 int /*<<< orphan*/  cpu_setsize ; 
 int /*<<< orphan*/  err (int,char*) ; 
 int /*<<< orphan*/  errx (int,char*,...) ; 
 int max_cpu_num ; 
 scalar_t__ pkg_selected_set ; 
 scalar_t__ strncmp (char*,char*,int) ; 
 int strtol (char*,char**,int) ; 
 int /*<<< orphan*/  usage () ; 
 int /*<<< orphan*/  validate_cpu_selected_set () ; 

void parse_cmdline_cpu(char *s)
{
	char *startp, *endp;
	int cpu = 0;

	if (pkg_selected_set) {
		usage();
		errx(1, "--cpu | --pkg");
	}
	cpu_selected_set = CPU_ALLOC((max_cpu_num + 1));
	if (cpu_selected_set == NULL)
		err(1, "cpu_selected_set");
	CPU_ZERO_S(cpu_setsize, cpu_selected_set);

	for (startp = s; startp && *startp;) {

		if (*startp == ',') {
			startp++;
			continue;
		}

		if (*startp == '-') {
			int end_cpu;

			startp++;
			end_cpu = strtol(startp, &endp, 10);
			if (startp == endp)
				continue;

			while (cpu <= end_cpu) {
				if (cpu > max_cpu_num)
					errx(1, "Requested cpu%d exceeds max cpu%d", cpu, max_cpu_num);
				CPU_SET_S(cpu, cpu_setsize, cpu_selected_set);
				cpu++;
			}
			startp = endp;
			continue;
		}

		if (strncmp(startp, "all", 3) == 0) {
			for (cpu = 0; cpu <= max_cpu_num; cpu += 1) {
				if (CPU_ISSET_S(cpu, cpu_setsize, cpu_present_set))
					CPU_SET_S(cpu, cpu_setsize, cpu_selected_set);
			}
			startp += 3;
			if (*startp == 0)
				break;
		}
		/* "--cpu even" is not documented */
		if (strncmp(startp, "even", 4) == 0) {
			for (cpu = 0; cpu <= max_cpu_num; cpu += 2) {
				if (CPU_ISSET_S(cpu, cpu_setsize, cpu_present_set))
					CPU_SET_S(cpu, cpu_setsize, cpu_selected_set);
			}
			startp += 4;
			if (*startp == 0)
				break;
		}

		/* "--cpu odd" is not documented */
		if (strncmp(startp, "odd", 3) == 0) {
			for (cpu = 1; cpu <= max_cpu_num; cpu += 2) {
				if (CPU_ISSET_S(cpu, cpu_setsize, cpu_present_set))
					CPU_SET_S(cpu, cpu_setsize, cpu_selected_set);
			}
			startp += 3;
			if (*startp == 0)
				break;
		}

		cpu = strtol(startp, &endp, 10);
		if (startp == endp)
			errx(1, "--cpu cpu-set: confused by '%s'", startp);
		if (cpu > max_cpu_num)
			errx(1, "Requested cpu%d exceeds max cpu%d", cpu, max_cpu_num);
		CPU_SET_S(cpu, cpu_setsize, cpu_selected_set);
		startp = endp;
	}

	validate_cpu_selected_set();

}