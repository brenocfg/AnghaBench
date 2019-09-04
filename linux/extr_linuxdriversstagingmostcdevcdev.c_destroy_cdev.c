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
struct comp_channel {int /*<<< orphan*/  list; int /*<<< orphan*/  cdev; int /*<<< orphan*/  devno; } ;
struct TYPE_2__ {int /*<<< orphan*/  class; } ;

/* Variables and functions */
 int /*<<< orphan*/  cdev_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ch_list_lock ; 
 TYPE_1__ comp ; 
 int /*<<< orphan*/  device_destroy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void destroy_cdev(struct comp_channel *c)
{
	unsigned long flags;

	device_destroy(comp.class, c->devno);
	cdev_del(&c->cdev);
	spin_lock_irqsave(&ch_list_lock, flags);
	list_del(&c->list);
	spin_unlock_irqrestore(&ch_list_lock, flags);
}