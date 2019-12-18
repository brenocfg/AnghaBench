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
struct k_itimer {int /*<<< orphan*/  it_lock; int /*<<< orphan*/  list; } ;

/* Variables and functions */
 int /*<<< orphan*/  IT_ID_SET ; 
 scalar_t__ TIMER_RETRY ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  release_posix_timer (struct k_itimer*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 
 scalar_t__ timer_delete_hook (struct k_itimer*) ; 

__attribute__((used)) static void itimer_delete(struct k_itimer *timer)
{
retry_delete:
	spin_lock_irq(&timer->it_lock);

	if (timer_delete_hook(timer) == TIMER_RETRY) {
		spin_unlock_irq(&timer->it_lock);
		goto retry_delete;
	}
	list_del(&timer->list);

	spin_unlock_irq(&timer->it_lock);
	release_posix_timer(timer, IT_ID_SET);
}