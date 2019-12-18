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
struct hlist_head {int dummy; } ;
struct batadv_forw_packet {int /*<<< orphan*/  delayed_work; int /*<<< orphan*/  list; int /*<<< orphan*/  cleanup_list; } ;
typedef  int /*<<< orphan*/  spinlock_t ;

/* Variables and functions */
 int /*<<< orphan*/  WARN_ONCE (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  batadv_event_workqueue ; 
 scalar_t__ batadv_forw_packet_was_stolen (struct batadv_forw_packet*) ; 
 int /*<<< orphan*/  hlist_add_head (int /*<<< orphan*/ *,struct hlist_head*) ; 
 int /*<<< orphan*/  hlist_del_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hlist_fake (int /*<<< orphan*/ *) ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  queue_delayed_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void batadv_forw_packet_queue(struct batadv_forw_packet *forw_packet,
				     spinlock_t *lock, struct hlist_head *head,
				     unsigned long send_time)
{
	spin_lock_bh(lock);

	/* did purging routine steal it from us? */
	if (batadv_forw_packet_was_stolen(forw_packet)) {
		/* If you got it for free() without trouble, then
		 * don't get back into the queue after stealing...
		 */
		WARN_ONCE(hlist_fake(&forw_packet->cleanup_list),
			  "Requeuing after batadv_forw_packet_steal() not allowed!\n");

		spin_unlock_bh(lock);
		return;
	}

	hlist_del_init(&forw_packet->list);
	hlist_add_head(&forw_packet->list, head);

	queue_delayed_work(batadv_event_workqueue,
			   &forw_packet->delayed_work,
			   send_time - jiffies);
	spin_unlock_bh(lock);
}