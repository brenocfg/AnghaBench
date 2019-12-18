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
struct cpufreq_policy {char* governor; void* max; void* min; } ;
struct cpufreq_affected_cpus {int /*<<< orphan*/  cpu; struct cpufreq_affected_cpus* next; } ;

/* Variables and functions */
 int EINVAL ; 
 char* _ (char*) ; 
 unsigned int bitmask_first (int /*<<< orphan*/ ) ; 
 scalar_t__ bitmask_isallclear (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bitmask_isbitset (int /*<<< orphan*/ ,unsigned int) ; 
 unsigned int bitmask_last (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bitmask_setall (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bitmask_setbit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct cpufreq_affected_cpus* cpufreq_get_related_cpus (unsigned int) ; 
 int /*<<< orphan*/  cpufreq_put_related_cpus (struct cpufreq_affected_cpus*) ; 
 int cpupower_is_cpu_online (unsigned int) ; 
 int /*<<< orphan*/  cpus_chosen ; 
 int do_one_cpu (unsigned int,struct cpufreq_policy*,unsigned long,int) ; 
 int getopt_long (int,char**,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  print_error () ; 
 int /*<<< orphan*/  print_unknown_arg () ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/  set_opts ; 
 int sscanf (char*,char*,char*) ; 
 void* string_to_frequency (char*) ; 
 int strlen (char*) ; 

int cmd_freq_set(int argc, char **argv)
{
	extern char *optarg;
	extern int optind, opterr, optopt;
	int ret = 0, cont = 1;
	int double_parm = 0, related = 0, policychange = 0;
	unsigned long freq = 0;
	char gov[20];
	unsigned int cpu;

	struct cpufreq_policy new_pol = {
		.min = 0,
		.max = 0,
		.governor = NULL,
	};

	/* parameter parsing */
	do {
		ret = getopt_long(argc, argv, "d:u:g:f:r", set_opts, NULL);
		switch (ret) {
		case '?':
			print_unknown_arg();
			return -EINVAL;
		case -1:
			cont = 0;
			break;
		case 'r':
			if (related)
				double_parm++;
			related++;
			break;
		case 'd':
			if (new_pol.min)
				double_parm++;
			policychange++;
			new_pol.min = string_to_frequency(optarg);
			if (new_pol.min == 0) {
				print_unknown_arg();
				return -EINVAL;
			}
			break;
		case 'u':
			if (new_pol.max)
				double_parm++;
			policychange++;
			new_pol.max = string_to_frequency(optarg);
			if (new_pol.max == 0) {
				print_unknown_arg();
				return -EINVAL;
			}
			break;
		case 'f':
			if (freq)
				double_parm++;
			freq = string_to_frequency(optarg);
			if (freq == 0) {
				print_unknown_arg();
				return -EINVAL;
			}
			break;
		case 'g':
			if (new_pol.governor)
				double_parm++;
			policychange++;
			if ((strlen(optarg) < 3) || (strlen(optarg) > 18)) {
				print_unknown_arg();
				return -EINVAL;
			}
			if ((sscanf(optarg, "%19s", gov)) != 1) {
				print_unknown_arg();
				return -EINVAL;
			}
			new_pol.governor = gov;
			break;
		}
	} while (cont);

	/* parameter checking */
	if (double_parm) {
		printf("the same parameter was passed more than once\n");
		return -EINVAL;
	}

	if (freq && policychange) {
		printf(_("the -f/--freq parameter cannot be combined with -d/--min, -u/--max or\n"
				"-g/--governor parameters\n"));
		return -EINVAL;
	}

	if (!freq && !policychange) {
		printf(_("At least one parameter out of -f/--freq, -d/--min, -u/--max, and\n"
				"-g/--governor must be passed\n"));
		return -EINVAL;
	}

	/* Default is: set all CPUs */
	if (bitmask_isallclear(cpus_chosen))
		bitmask_setall(cpus_chosen);

	/* Also set frequency settings for related CPUs if -r is passed */
	if (related) {
		for (cpu = bitmask_first(cpus_chosen);
		     cpu <= bitmask_last(cpus_chosen); cpu++) {
			struct cpufreq_affected_cpus *cpus;

			if (!bitmask_isbitset(cpus_chosen, cpu) ||
			    cpupower_is_cpu_online(cpu) != 1)
				continue;

			cpus = cpufreq_get_related_cpus(cpu);
			if (!cpus)
				break;
			while (cpus->next) {
				bitmask_setbit(cpus_chosen, cpus->cpu);
				cpus = cpus->next;
			}
			/* Set the last cpu in related cpus list */
			bitmask_setbit(cpus_chosen, cpus->cpu);
			cpufreq_put_related_cpus(cpus);
		}
	}


	/* loop over CPUs */
	for (cpu = bitmask_first(cpus_chosen);
	     cpu <= bitmask_last(cpus_chosen); cpu++) {

		if (!bitmask_isbitset(cpus_chosen, cpu) ||
		    cpupower_is_cpu_online(cpu) != 1)
			continue;

		printf(_("Setting cpu: %d\n"), cpu);
		ret = do_one_cpu(cpu, &new_pol, freq, policychange);
		if (ret) {
			print_error();
			return ret;
		}
	}

	return 0;
}