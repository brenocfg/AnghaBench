#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct net_device {int dummy; } ;
struct TYPE_5__ {TYPE_1__* proto; int /*<<< orphan*/  state_lock; scalar_t__ carrier; scalar_t__ open; } ;
typedef  TYPE_2__ hdlc_device ;
struct TYPE_4__ {int /*<<< orphan*/  (* close ) (struct net_device*) ;} ;

/* Variables and functions */
 TYPE_2__* dev_to_hdlc (struct net_device*) ; 
 int /*<<< orphan*/  hdlc_proto_stop (struct net_device*) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (struct net_device*) ; 

void hdlc_close(struct net_device *dev)
{
	hdlc_device *hdlc = dev_to_hdlc(dev);
#ifdef DEBUG_LINK
	printk(KERN_DEBUG "%s: hdlc_close() carrier %i open %i\n", dev->name,
	       hdlc->carrier, hdlc->open);
#endif

	spin_lock_irq(&hdlc->state_lock);

	hdlc->open = 0;
	if (hdlc->carrier)
		hdlc_proto_stop(dev);

	spin_unlock_irq(&hdlc->state_lock);

	if (hdlc->proto->close)
		hdlc->proto->close(dev);
}