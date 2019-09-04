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
struct TYPE_2__ {int /*<<< orphan*/  lock; } ;
struct fs_pin {int done; TYPE_1__ wait; int /*<<< orphan*/  s_list; int /*<<< orphan*/  m_list; } ;

/* Variables and functions */
 int /*<<< orphan*/  hlist_del_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pin_lock ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wake_up_locked (TYPE_1__*) ; 

void pin_remove(struct fs_pin *pin)
{
	spin_lock(&pin_lock);
	hlist_del_init(&pin->m_list);
	hlist_del_init(&pin->s_list);
	spin_unlock(&pin_lock);
	spin_lock_irq(&pin->wait.lock);
	pin->done = 1;
	wake_up_locked(&pin->wait);
	spin_unlock_irq(&pin->wait.lock);
}