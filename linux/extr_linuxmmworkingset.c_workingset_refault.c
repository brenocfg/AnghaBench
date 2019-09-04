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
struct pglist_data {int dummy; } ;
struct mem_cgroup {int dummy; } ;
struct lruvec {int /*<<< orphan*/  inactive_age; } ;

/* Variables and functions */
 unsigned long EVICTION_MASK ; 
 int /*<<< orphan*/  LRU_ACTIVE_FILE ; 
 int /*<<< orphan*/  MAX_NR_ZONES ; 
 int /*<<< orphan*/  WORKINGSET_ACTIVATE ; 
 int /*<<< orphan*/  WORKINGSET_REFAULT ; 
 unsigned long atomic_long_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  inc_lruvec_state (struct lruvec*,int /*<<< orphan*/ ) ; 
 unsigned long lruvec_lru_size (struct lruvec*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mem_cgroup_disabled () ; 
 struct mem_cgroup* mem_cgroup_from_id (int) ; 
 struct lruvec* mem_cgroup_lruvec (struct pglist_data*,struct mem_cgroup*) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 
 int /*<<< orphan*/  unpack_shadow (void*,int*,struct pglist_data**,unsigned long*) ; 

bool workingset_refault(void *shadow)
{
	unsigned long refault_distance;
	unsigned long active_file;
	struct mem_cgroup *memcg;
	unsigned long eviction;
	struct lruvec *lruvec;
	unsigned long refault;
	struct pglist_data *pgdat;
	int memcgid;

	unpack_shadow(shadow, &memcgid, &pgdat, &eviction);

	rcu_read_lock();
	/*
	 * Look up the memcg associated with the stored ID. It might
	 * have been deleted since the page's eviction.
	 *
	 * Note that in rare events the ID could have been recycled
	 * for a new cgroup that refaults a shared page. This is
	 * impossible to tell from the available data. However, this
	 * should be a rare and limited disturbance, and activations
	 * are always speculative anyway. Ultimately, it's the aging
	 * algorithm's job to shake out the minimum access frequency
	 * for the active cache.
	 *
	 * XXX: On !CONFIG_MEMCG, this will always return NULL; it
	 * would be better if the root_mem_cgroup existed in all
	 * configurations instead.
	 */
	memcg = mem_cgroup_from_id(memcgid);
	if (!mem_cgroup_disabled() && !memcg) {
		rcu_read_unlock();
		return false;
	}
	lruvec = mem_cgroup_lruvec(pgdat, memcg);
	refault = atomic_long_read(&lruvec->inactive_age);
	active_file = lruvec_lru_size(lruvec, LRU_ACTIVE_FILE, MAX_NR_ZONES);

	/*
	 * The unsigned subtraction here gives an accurate distance
	 * across inactive_age overflows in most cases.
	 *
	 * There is a special case: usually, shadow entries have a
	 * short lifetime and are either refaulted or reclaimed along
	 * with the inode before they get too old.  But it is not
	 * impossible for the inactive_age to lap a shadow entry in
	 * the field, which can then can result in a false small
	 * refault distance, leading to a false activation should this
	 * old entry actually refault again.  However, earlier kernels
	 * used to deactivate unconditionally with *every* reclaim
	 * invocation for the longest time, so the occasional
	 * inappropriate activation leading to pressure on the active
	 * list is not a problem.
	 */
	refault_distance = (refault - eviction) & EVICTION_MASK;

	inc_lruvec_state(lruvec, WORKINGSET_REFAULT);

	if (refault_distance <= active_file) {
		inc_lruvec_state(lruvec, WORKINGSET_ACTIVATE);
		rcu_read_unlock();
		return true;
	}
	rcu_read_unlock();
	return false;
}