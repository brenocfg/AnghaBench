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
struct fc_exch {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  SLAB_HWCACHE_ALIGN ; 
 int /*<<< orphan*/  create_singlethread_workqueue (char*) ; 
 int fc_cpu_mask ; 
 int fc_cpu_order ; 
 int /*<<< orphan*/  fc_em_cachep ; 
 int /*<<< orphan*/  fc_exch_workqueue ; 
 int ilog2 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kmem_cache_create (char*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kmem_cache_destroy (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nr_cpu_ids ; 
 int /*<<< orphan*/  roundup_pow_of_two (int /*<<< orphan*/ ) ; 

int fc_setup_exch_mgr(void)
{
	fc_em_cachep = kmem_cache_create("libfc_em", sizeof(struct fc_exch),
					 0, SLAB_HWCACHE_ALIGN, NULL);
	if (!fc_em_cachep)
		return -ENOMEM;

	/*
	 * Initialize fc_cpu_mask and fc_cpu_order. The
	 * fc_cpu_mask is set for nr_cpu_ids rounded up
	 * to order of 2's * power and order is stored
	 * in fc_cpu_order as this is later required in
	 * mapping between an exch id and exch array index
	 * in per cpu exch pool.
	 *
	 * This round up is required to align fc_cpu_mask
	 * to exchange id's lower bits such that all incoming
	 * frames of an exchange gets delivered to the same
	 * cpu on which exchange originated by simple bitwise
	 * AND operation between fc_cpu_mask and exchange id.
	 */
	fc_cpu_order = ilog2(roundup_pow_of_two(nr_cpu_ids));
	fc_cpu_mask = (1 << fc_cpu_order) - 1;

	fc_exch_workqueue = create_singlethread_workqueue("fc_exch_workqueue");
	if (!fc_exch_workqueue)
		goto err;
	return 0;
err:
	kmem_cache_destroy(fc_em_cachep);
	return -ENOMEM;
}