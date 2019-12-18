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
struct afs_vl_cursor {unsigned long untried; int index; TYPE_1__* server_list; int /*<<< orphan*/  error; struct afs_cell* cell; } ;
struct afs_cell {scalar_t__ dns_source; scalar_t__ dns_expiry; int /*<<< orphan*/  vl_servers_lock; int /*<<< orphan*/  vl_servers; int /*<<< orphan*/  dns_lookup_count; int /*<<< orphan*/  manager; int /*<<< orphan*/  flags; } ;
struct TYPE_2__ {unsigned long nr_servers; } ;

/* Variables and functions */
 int /*<<< orphan*/  AFS_CELL_FL_DO_LOOKUP ; 
 scalar_t__ DNS_RECORD_UNAVAILABLE ; 
 int /*<<< orphan*/  EDESTADDRREQ ; 
 int /*<<< orphan*/  ERESTARTSYS ; 
 TYPE_1__* afs_get_vlserverlist (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  afs_wq ; 
 scalar_t__ ktime_get_real_seconds () ; 
 int /*<<< orphan*/  lockdep_is_held (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  queue_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rcu_dereference_protected (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  read_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  read_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 unsigned int smp_load_acquire (int /*<<< orphan*/ *) ; 
 scalar_t__ wait_var_event_interruptible (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static bool afs_start_vl_iteration(struct afs_vl_cursor *vc)
{
	struct afs_cell *cell = vc->cell;
	unsigned int dns_lookup_count;

	if (cell->dns_source == DNS_RECORD_UNAVAILABLE ||
	    cell->dns_expiry <= ktime_get_real_seconds()) {
		dns_lookup_count = smp_load_acquire(&cell->dns_lookup_count);
		set_bit(AFS_CELL_FL_DO_LOOKUP, &cell->flags);
		queue_work(afs_wq, &cell->manager);

		if (cell->dns_source == DNS_RECORD_UNAVAILABLE) {
			if (wait_var_event_interruptible(
				    &cell->dns_lookup_count,
				    smp_load_acquire(&cell->dns_lookup_count)
				    != dns_lookup_count) < 0) {
				vc->error = -ERESTARTSYS;
				return false;
			}
		}

		/* Status load is ordered after lookup counter load */
		if (cell->dns_source == DNS_RECORD_UNAVAILABLE) {
			vc->error = -EDESTADDRREQ;
			return false;
		}
	}

	read_lock(&cell->vl_servers_lock);
	vc->server_list = afs_get_vlserverlist(
		rcu_dereference_protected(cell->vl_servers,
					  lockdep_is_held(&cell->vl_servers_lock)));
	read_unlock(&cell->vl_servers_lock);
	if (!vc->server_list->nr_servers)
		return false;

	vc->untried = (1UL << vc->server_list->nr_servers) - 1;
	vc->index = -1;
	return true;
}