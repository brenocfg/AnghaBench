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
struct TYPE_3__ {double nr_loops; scalar_t__ show_details; } ;
struct TYPE_4__ {TYPE_1__ p; } ;

/* Variables and functions */
 double NSEC_PER_SEC ; 
 int /*<<< orphan*/  calc_convergence (double,double*) ; 
 int /*<<< orphan*/  fflush (int /*<<< orphan*/ ) ; 
 TYPE_2__* g ; 
 int /*<<< orphan*/  stdout ; 
 int /*<<< orphan*/  tprintf (char*,double,double) ; 

__attribute__((used)) static void show_summary(double runtime_ns_max, int l, double *convergence)
{
	tprintf("\r #  %5.1f%%  [%.1f mins]",
		(double)(l+1)/g->p.nr_loops*100.0, runtime_ns_max / NSEC_PER_SEC / 60.0);

	calc_convergence(runtime_ns_max, convergence);

	if (g->p.show_details >= 0)
		fflush(stdout);
}