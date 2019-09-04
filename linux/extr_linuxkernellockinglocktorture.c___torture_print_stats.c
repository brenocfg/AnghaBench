#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct lock_stress_stats {long n_lock_acquired; long n_lock_fail; } ;
struct TYPE_2__ {int nrealwriters_stress; int nrealreaders_stress; int /*<<< orphan*/  n_lock_torture_errors; } ;

/* Variables and functions */
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 TYPE_1__ cxt ; 
 int /*<<< orphan*/  sprintf (char*,char*,char*,long long,long,long,char*,int,char*) ; 

__attribute__((used)) static void __torture_print_stats(char *page,
				  struct lock_stress_stats *statp, bool write)
{
	bool fail = 0;
	int i, n_stress;
	long max = 0, min = statp ? statp[0].n_lock_acquired : 0;
	long long sum = 0;

	n_stress = write ? cxt.nrealwriters_stress : cxt.nrealreaders_stress;
	for (i = 0; i < n_stress; i++) {
		if (statp[i].n_lock_fail)
			fail = true;
		sum += statp[i].n_lock_acquired;
		if (max < statp[i].n_lock_fail)
			max = statp[i].n_lock_fail;
		if (min > statp[i].n_lock_fail)
			min = statp[i].n_lock_fail;
	}
	page += sprintf(page,
			"%s:  Total: %lld  Max/Min: %ld/%ld %s  Fail: %d %s\n",
			write ? "Writes" : "Reads ",
			sum, max, min, max / 2 > min ? "???" : "",
			fail, fail ? "!!!" : "");
	if (fail)
		atomic_inc(&cxt.n_lock_torture_errors);
}