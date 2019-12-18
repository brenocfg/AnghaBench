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
struct fib_nh_common {int /*<<< orphan*/  nhc_rth_input; int /*<<< orphan*/  nhc_pcpu_rth_output; int /*<<< orphan*/  nhc_lwtstate; scalar_t__ nhc_dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_put (scalar_t__) ; 
 int /*<<< orphan*/  free_nh_exceptions (struct fib_nh_common*) ; 
 int /*<<< orphan*/  lwtstate_put (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rt_fibinfo_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rt_fibinfo_free_cpus (int /*<<< orphan*/ ) ; 

void fib_nh_common_release(struct fib_nh_common *nhc)
{
	if (nhc->nhc_dev)
		dev_put(nhc->nhc_dev);

	lwtstate_put(nhc->nhc_lwtstate);
	rt_fibinfo_free_cpus(nhc->nhc_pcpu_rth_output);
	rt_fibinfo_free(&nhc->nhc_rth_input);
	free_nh_exceptions(nhc);
}