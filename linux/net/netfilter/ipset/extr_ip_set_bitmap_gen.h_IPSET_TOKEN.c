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
typedef  scalar_t__ u32 ;
struct timer_list {int dummy; } ;
struct TYPE_2__ {scalar_t__ expires; } ;
struct mtype {scalar_t__ elements; TYPE_1__ gc; int /*<<< orphan*/  members; struct ip_set* set; } ;
struct ip_set {int /*<<< orphan*/  timeout; int /*<<< orphan*/  lock; int /*<<< orphan*/  elements; int /*<<< orphan*/  dsize; } ;

/* Variables and functions */
 int HZ ; 
 int IPSET_GC_PERIOD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  add_timer (TYPE_1__*) ; 
 int /*<<< orphan*/  clear_bit (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ext_timeout (void*,struct ip_set*) ; 
 struct mtype* from_timer (int /*<<< orphan*/ ,struct timer_list*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gc ; 
 void* get_ext (struct ip_set*,struct mtype*,scalar_t__) ; 
 int /*<<< orphan*/  ip_set_ext_destroy (struct ip_set*,void*) ; 
 scalar_t__ ip_set_timeout_expired (int /*<<< orphan*/ ) ; 
 scalar_t__ jiffies ; 
 struct mtype* map ; 
 scalar_t__ mtype_gc_test (scalar_t__,struct mtype*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
mtype_gc(struct timer_list *t)
{
	struct mtype *map = from_timer(map, t, gc);
	struct ip_set *set = map->set;
	void *x;
	u32 id;

	/* We run parallel with other readers (test element)
	 * but adding/deleting new entries is locked out
	 */
	spin_lock_bh(&set->lock);
	for (id = 0; id < map->elements; id++)
		if (mtype_gc_test(id, map, set->dsize)) {
			x = get_ext(set, map, id);
			if (ip_set_timeout_expired(ext_timeout(x, set))) {
				clear_bit(id, map->members);
				ip_set_ext_destroy(set, x);
				set->elements--;
			}
		}
	spin_unlock_bh(&set->lock);

	map->gc.expires = jiffies + IPSET_GC_PERIOD(set->timeout) * HZ;
	add_timer(&map->gc);
}