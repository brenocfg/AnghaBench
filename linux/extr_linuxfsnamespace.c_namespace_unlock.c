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

/* Variables and functions */
 int /*<<< orphan*/  group_pin_kill (struct hlist_head*) ; 
 int /*<<< orphan*/  hlist_empty (struct hlist_head*) ; 
 int /*<<< orphan*/  hlist_move_list (int /*<<< orphan*/ *,struct hlist_head*) ; 
 scalar_t__ likely (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  namespace_sem ; 
 int /*<<< orphan*/  synchronize_rcu () ; 
 int /*<<< orphan*/  unmounted ; 
 int /*<<< orphan*/  up_write (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void namespace_unlock(void)
{
	struct hlist_head head;

	hlist_move_list(&unmounted, &head);

	up_write(&namespace_sem);

	if (likely(hlist_empty(&head)))
		return;

	synchronize_rcu();

	group_pin_kill(&head);
}