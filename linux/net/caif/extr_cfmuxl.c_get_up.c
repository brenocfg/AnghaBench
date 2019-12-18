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
typedef  scalar_t__ u16 ;
struct cfmuxl {int /*<<< orphan*/  receive_lock; int /*<<< orphan*/ * up_cache; int /*<<< orphan*/  srvl_list; } ;
struct cflayer {scalar_t__ id; } ;

/* Variables and functions */
 scalar_t__ UP_CACHE_SIZE ; 
 struct cflayer* get_from_id (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  rcu_assign_pointer (int /*<<< orphan*/ ,struct cflayer*) ; 
 struct cflayer* rcu_dereference (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 

__attribute__((used)) static struct cflayer *get_up(struct cfmuxl *muxl, u16 id)
{
	struct cflayer *up;
	int idx = id % UP_CACHE_SIZE;
	up = rcu_dereference(muxl->up_cache[idx]);
	if (up == NULL || up->id != id) {
		spin_lock_bh(&muxl->receive_lock);
		up = get_from_id(&muxl->srvl_list, id);
		rcu_assign_pointer(muxl->up_cache[idx], up);
		spin_unlock_bh(&muxl->receive_lock);
	}
	return up;
}