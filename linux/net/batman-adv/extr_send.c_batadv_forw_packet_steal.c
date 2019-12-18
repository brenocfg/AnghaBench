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
struct batadv_forw_packet {int /*<<< orphan*/  cleanup_list; int /*<<< orphan*/  list; } ;
typedef  int /*<<< orphan*/  spinlock_t ;

/* Variables and functions */
 scalar_t__ batadv_forw_packet_was_stolen (struct batadv_forw_packet*) ; 
 int /*<<< orphan*/  hlist_add_fake (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hlist_del_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 

bool batadv_forw_packet_steal(struct batadv_forw_packet *forw_packet,
			      spinlock_t *lock)
{
	/* did purging routine steal it earlier? */
	spin_lock_bh(lock);
	if (batadv_forw_packet_was_stolen(forw_packet)) {
		spin_unlock_bh(lock);
		return false;
	}

	hlist_del_init(&forw_packet->list);

	/* Just to spot misuse of this function */
	hlist_add_fake(&forw_packet->cleanup_list);

	spin_unlock_bh(lock);
	return true;
}