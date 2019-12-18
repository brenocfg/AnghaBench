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
struct switch_tracking {int* tids; int nr_tids; } ;
typedef  int /*<<< orphan*/  pid_t ;

/* Variables and functions */
 int* calloc (int,int) ; 
 void* realloc (int*,int) ; 

__attribute__((used)) static int check_cpu(struct switch_tracking *switch_tracking, int cpu)
{
	int i, nr = cpu + 1;

	if (cpu < 0)
		return -1;

	if (!switch_tracking->tids) {
		switch_tracking->tids = calloc(nr, sizeof(pid_t));
		if (!switch_tracking->tids)
			return -1;
		for (i = 0; i < nr; i++)
			switch_tracking->tids[i] = -1;
		switch_tracking->nr_tids = nr;
		return 0;
	}

	if (cpu >= switch_tracking->nr_tids) {
		void *addr;

		addr = realloc(switch_tracking->tids, nr * sizeof(pid_t));
		if (!addr)
			return -1;
		switch_tracking->tids = addr;
		for (i = switch_tracking->nr_tids; i < nr; i++)
			switch_tracking->tids[i] = -1;
		switch_tracking->nr_tids = nr;
		return 0;
	}

	return 0;
}