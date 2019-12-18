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
 int /*<<< orphan*/  nf_conntrack_locks_all ; 
 int /*<<< orphan*/  nf_conntrack_locks_all_lock ; 
 int /*<<< orphan*/  smp_store_release (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void nf_conntrack_all_unlock(void)
{
	/* All prior stores must be complete before we clear
	 * 'nf_conntrack_locks_all'. Otherwise nf_conntrack_lock()
	 * might observe the false value but not the entire
	 * critical section.
	 * It pairs with the smp_load_acquire() in nf_conntrack_lock()
	 */
	smp_store_release(&nf_conntrack_locks_all, false);
	spin_unlock(&nf_conntrack_locks_all_lock);
}