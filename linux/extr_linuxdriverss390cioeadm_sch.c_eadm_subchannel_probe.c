#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_3__ {int /*<<< orphan*/  kobj; } ;
struct subchannel {TYPE_1__ dev; int /*<<< orphan*/ * lock; int /*<<< orphan*/  isc; } ;
struct eadm_private {int /*<<< orphan*/  head; struct subchannel* sch; int /*<<< orphan*/  state; int /*<<< orphan*/  timer; } ;

/* Variables and functions */
 int /*<<< orphan*/  EADM_IDLE ; 
 int /*<<< orphan*/  EADM_SCH_ISC ; 
 int ENOMEM ; 
 int GFP_DMA ; 
 int GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  KOBJ_ADD ; 
 int cio_enable_subchannel (struct subchannel*,int /*<<< orphan*/ ) ; 
 scalar_t__ dev_get_uevent_suppress (TYPE_1__*) ; 
 int /*<<< orphan*/  dev_set_uevent_suppress (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  eadm_list ; 
 int /*<<< orphan*/  eadm_subchannel_timeout ; 
 int /*<<< orphan*/  kfree (struct eadm_private*) ; 
 int /*<<< orphan*/  kobject_uevent (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct eadm_private* kzalloc (int,int) ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_lock ; 
 int /*<<< orphan*/  set_eadm_private (struct subchannel*,struct eadm_private*) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  timer_setup (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int eadm_subchannel_probe(struct subchannel *sch)
{
	struct eadm_private *private;
	int ret;

	private = kzalloc(sizeof(*private), GFP_KERNEL | GFP_DMA);
	if (!private)
		return -ENOMEM;

	INIT_LIST_HEAD(&private->head);
	timer_setup(&private->timer, eadm_subchannel_timeout, 0);

	spin_lock_irq(sch->lock);
	set_eadm_private(sch, private);
	private->state = EADM_IDLE;
	private->sch = sch;
	sch->isc = EADM_SCH_ISC;
	ret = cio_enable_subchannel(sch, (u32)(unsigned long)sch);
	if (ret) {
		set_eadm_private(sch, NULL);
		spin_unlock_irq(sch->lock);
		kfree(private);
		goto out;
	}
	spin_unlock_irq(sch->lock);

	spin_lock_irq(&list_lock);
	list_add(&private->head, &eadm_list);
	spin_unlock_irq(&list_lock);

	if (dev_get_uevent_suppress(&sch->dev)) {
		dev_set_uevent_suppress(&sch->dev, 0);
		kobject_uevent(&sch->dev.kobj, KOBJ_ADD);
	}
out:
	return ret;
}