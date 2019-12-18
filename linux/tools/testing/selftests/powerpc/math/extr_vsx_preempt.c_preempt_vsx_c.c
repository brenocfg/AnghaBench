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
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*) ; 
 long preempt_vsx (scalar_t__**,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_self () ; 
 scalar_t__ rand () ; 
 int /*<<< orphan*/  running ; 
 int /*<<< orphan*/  srand (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  threads_starting ; 
 scalar_t__** varray ; 

void *preempt_vsx_c(void *p)
{
	int i, j;
	long rc;
	srand(pthread_self());
	for (i = 0; i < 12; i++)
		for (j = 0; j < 4; j++) {
			varray[i][j] = rand();
			/* Don't want zero because it hides kernel problems */
			if (varray[i][j] == 0)
				j--;
		}
	rc = preempt_vsx(varray, &threads_starting, &running);
	if (rc == 2)
		fprintf(stderr, "Caught zeros in VSX compares\n");
	return (void *)rc;
}