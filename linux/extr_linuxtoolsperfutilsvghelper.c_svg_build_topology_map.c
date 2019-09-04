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
typedef  int /*<<< orphan*/  cpumask_t ;

/* Variables and functions */
 int MAX_NR_CPUS ; 
 void* calloc (int,int) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*) ; 
 int* malloc (int) ; 
 int /*<<< orphan*/  scan_core_topology (int*,struct topology*) ; 
 int /*<<< orphan*/  stderr ; 
 scalar_t__ str_to_bitmap (char*,int /*<<< orphan*/ *) ; 
 scalar_t__ strlen (char*) ; 
 int* topology_map ; 
 int /*<<< orphan*/  zfree (int /*<<< orphan*/ **) ; 

int svg_build_topology_map(char *sib_core, int sib_core_nr,
			   char *sib_thr, int sib_thr_nr)
{
	int i;
	struct topology t;

	t.sib_core_nr = sib_core_nr;
	t.sib_thr_nr = sib_thr_nr;
	t.sib_core = calloc(sib_core_nr, sizeof(cpumask_t));
	t.sib_thr = calloc(sib_thr_nr, sizeof(cpumask_t));

	if (!t.sib_core || !t.sib_thr) {
		fprintf(stderr, "topology: no memory\n");
		goto exit;
	}

	for (i = 0; i < sib_core_nr; i++) {
		if (str_to_bitmap(sib_core, &t.sib_core[i])) {
			fprintf(stderr, "topology: can't parse siblings map\n");
			goto exit;
		}

		sib_core += strlen(sib_core) + 1;
	}

	for (i = 0; i < sib_thr_nr; i++) {
		if (str_to_bitmap(sib_thr, &t.sib_thr[i])) {
			fprintf(stderr, "topology: can't parse siblings map\n");
			goto exit;
		}

		sib_thr += strlen(sib_thr) + 1;
	}

	topology_map = malloc(sizeof(int) * MAX_NR_CPUS);
	if (!topology_map) {
		fprintf(stderr, "topology: no memory\n");
		goto exit;
	}

	for (i = 0; i < MAX_NR_CPUS; i++)
		topology_map[i] = -1;

	scan_core_topology(topology_map, &t);

	return 0;

exit:
	zfree(&t.sib_core);
	zfree(&t.sib_thr);

	return -1;
}