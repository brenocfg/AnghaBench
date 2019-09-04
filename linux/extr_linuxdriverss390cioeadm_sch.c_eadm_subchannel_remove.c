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
struct subchannel {int /*<<< orphan*/ * lock; } ;
struct eadm_private {int /*<<< orphan*/  head; } ;

/* Variables and functions */
 int /*<<< orphan*/  eadm_quiesce (struct subchannel*) ; 
 struct eadm_private* get_eadm_private (struct subchannel*) ; 
 int /*<<< orphan*/  kfree (struct eadm_private*) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_lock ; 
 int /*<<< orphan*/  set_eadm_private (struct subchannel*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int eadm_subchannel_remove(struct subchannel *sch)
{
	struct eadm_private *private = get_eadm_private(sch);

	spin_lock_irq(&list_lock);
	list_del(&private->head);
	spin_unlock_irq(&list_lock);

	eadm_quiesce(sch);

	spin_lock_irq(sch->lock);
	set_eadm_private(sch, NULL);
	spin_unlock_irq(sch->lock);

	kfree(private);

	return 0;
}