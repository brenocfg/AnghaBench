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
struct topology {int sib_core_nr; int sib_thr_nr; int /*<<< orphan*/ * sib_thr; int /*<<< orphan*/ * sib_core; } ;
struct perf_env {int nr_sibling_cores; int nr_sibling_threads; char* sibling_cores; char* sibling_threads; int /*<<< orphan*/  nr_cpus_online; } ;
typedef  int /*<<< orphan*/  cpumask_t ;

/* Variables and functions */
 int /*<<< orphan*/  MAX_NR_CPUS ; 
 void* calloc (int,int) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*) ; 
 int* malloc (int) ; 
 int min (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  scan_core_topology (int*,struct topology*,int) ; 
 int /*<<< orphan*/  stderr ; 
 scalar_t__ str_to_bitmap (char*,int /*<<< orphan*/ *,int) ; 
 scalar_t__ strlen (char*) ; 
 int* topology_map ; 
 int /*<<< orphan*/  zfree (int /*<<< orphan*/ **) ; 

int svg_build_topology_map(struct perf_env *env)
{
	int i, nr_cpus;
	struct topology t;
	char *sib_core, *sib_thr;

	nr_cpus = min(env->nr_cpus_online, MAX_NR_CPUS);

	t.sib_core_nr = env->nr_sibling_cores;
	t.sib_thr_nr = env->nr_sibling_threads;
	t.sib_core = calloc(env->nr_sibling_cores, sizeof(cpumask_t));
	t.sib_thr = calloc(env->nr_sibling_threads, sizeof(cpumask_t));

	sib_core = env->sibling_cores;
	sib_thr = env->sibling_threads;

	if (!t.sib_core || !t.sib_thr) {
		fprintf(stderr, "topology: no memory\n");
		goto exit;
	}

	for (i = 0; i < env->nr_sibling_cores; i++) {
		if (str_to_bitmap(sib_core, &t.sib_core[i], nr_cpus)) {
			fprintf(stderr, "topology: can't parse siblings map\n");
			goto exit;
		}

		sib_core += strlen(sib_core) + 1;
	}

	for (i = 0; i < env->nr_sibling_threads; i++) {
		if (str_to_bitmap(sib_thr, &t.sib_thr[i], nr_cpus)) {
			fprintf(stderr, "topology: can't parse siblings map\n");
			goto exit;
		}

		sib_thr += strlen(sib_thr) + 1;
	}

	topology_map = malloc(sizeof(int) * nr_cpus);
	if (!topology_map) {
		fprintf(stderr, "topology: no memory\n");
		goto exit;
	}

	for (i = 0; i < nr_cpus; i++)
		topology_map[i] = -1;

	scan_core_topology(topology_map, &t, nr_cpus);

	return 0;

exit:
	zfree(&t.sib_core);
	zfree(&t.sib_thr);

	return -1;
}