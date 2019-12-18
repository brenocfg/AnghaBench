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
struct thread_data {int /*<<< orphan*/  bind_cpumask; } ;
struct TYPE_3__ {int nr_tasks; int nr_cpus; int /*<<< orphan*/  cpu_list_str; } ;
struct TYPE_4__ {TYPE_1__ p; struct thread_data* threads; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  CPU_SET (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  CPU_ZERO (int /*<<< orphan*/ *) ; 
 int atol (char*) ; 
 int /*<<< orphan*/  dprintf (char*,...) ; 
 int /*<<< orphan*/  free (char*) ; 
 TYPE_2__* g ; 
 int /*<<< orphan*/  printf (char*,int,...) ; 
 char* strdup (int /*<<< orphan*/ ) ; 
 char* strsep (char**,char*) ; 
 char* strstr (char*,char*) ; 
 int /*<<< orphan*/  tprintf (char*,...) ; 

__attribute__((used)) static int parse_setup_cpu_list(void)
{
	struct thread_data *td;
	char *str0, *str;
	int t;

	if (!g->p.cpu_list_str)
		return 0;

	dprintf("g->p.nr_tasks: %d\n", g->p.nr_tasks);

	str0 = str = strdup(g->p.cpu_list_str);
	t = 0;

	BUG_ON(!str);

	tprintf("# binding tasks to CPUs:\n");
	tprintf("#  ");

	while (true) {
		int bind_cpu, bind_cpu_0, bind_cpu_1;
		char *tok, *tok_end, *tok_step, *tok_len, *tok_mul;
		int bind_len;
		int step;
		int mul;

		tok = strsep(&str, ",");
		if (!tok)
			break;

		tok_end = strstr(tok, "-");

		dprintf("\ntoken: {%s}, end: {%s}\n", tok, tok_end);
		if (!tok_end) {
			/* Single CPU specified: */
			bind_cpu_0 = bind_cpu_1 = atol(tok);
		} else {
			/* CPU range specified (for example: "5-11"): */
			bind_cpu_0 = atol(tok);
			bind_cpu_1 = atol(tok_end + 1);
		}

		step = 1;
		tok_step = strstr(tok, "#");
		if (tok_step) {
			step = atol(tok_step + 1);
			BUG_ON(step <= 0 || step >= g->p.nr_cpus);
		}

		/*
		 * Mask length.
		 * Eg: "--cpus 8_4-16#4" means: '--cpus 8_4,12_4,16_4',
		 * where the _4 means the next 4 CPUs are allowed.
		 */
		bind_len = 1;
		tok_len = strstr(tok, "_");
		if (tok_len) {
			bind_len = atol(tok_len + 1);
			BUG_ON(bind_len <= 0 || bind_len > g->p.nr_cpus);
		}

		/* Multiplicator shortcut, "0x8" is a shortcut for: "0,0,0,0,0,0,0,0" */
		mul = 1;
		tok_mul = strstr(tok, "x");
		if (tok_mul) {
			mul = atol(tok_mul + 1);
			BUG_ON(mul <= 0);
		}

		dprintf("CPUs: %d_%d-%d#%dx%d\n", bind_cpu_0, bind_len, bind_cpu_1, step, mul);

		if (bind_cpu_0 >= g->p.nr_cpus || bind_cpu_1 >= g->p.nr_cpus) {
			printf("\nTest not applicable, system has only %d CPUs.\n", g->p.nr_cpus);
			return -1;
		}

		BUG_ON(bind_cpu_0 < 0 || bind_cpu_1 < 0);
		BUG_ON(bind_cpu_0 > bind_cpu_1);

		for (bind_cpu = bind_cpu_0; bind_cpu <= bind_cpu_1; bind_cpu += step) {
			int i;

			for (i = 0; i < mul; i++) {
				int cpu;

				if (t >= g->p.nr_tasks) {
					printf("\n# NOTE: ignoring bind CPUs starting at CPU#%d\n #", bind_cpu);
					goto out;
				}
				td = g->threads + t;

				if (t)
					tprintf(",");
				if (bind_len > 1) {
					tprintf("%2d/%d", bind_cpu, bind_len);
				} else {
					tprintf("%2d", bind_cpu);
				}

				CPU_ZERO(&td->bind_cpumask);
				for (cpu = bind_cpu; cpu < bind_cpu+bind_len; cpu++) {
					BUG_ON(cpu < 0 || cpu >= g->p.nr_cpus);
					CPU_SET(cpu, &td->bind_cpumask);
				}
				t++;
			}
		}
	}
out:

	tprintf("\n");

	if (t < g->p.nr_tasks)
		printf("# NOTE: %d tasks bound, %d tasks unbound\n", t, g->p.nr_tasks - t);

	free(str0);
	return 0;
}