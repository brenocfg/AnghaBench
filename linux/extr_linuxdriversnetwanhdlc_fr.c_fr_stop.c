#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct net_device {int dummy; } ;
typedef  int /*<<< orphan*/  hdlc_device ;
struct TYPE_3__ {scalar_t__ lmi; } ;
struct TYPE_4__ {int /*<<< orphan*/  timer; TYPE_1__ settings; } ;

/* Variables and functions */
 scalar_t__ LMI_NONE ; 
 int /*<<< orphan*/  del_timer_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * dev_to_hdlc (struct net_device*) ; 
 int /*<<< orphan*/  fr_set_link_state (int /*<<< orphan*/ ,struct net_device*) ; 
 TYPE_2__* state (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void fr_stop(struct net_device *dev)
{
	hdlc_device *hdlc = dev_to_hdlc(dev);
#ifdef DEBUG_LINK
	printk(KERN_DEBUG "fr_stop\n");
#endif
	if (state(hdlc)->settings.lmi != LMI_NONE)
		del_timer_sync(&state(hdlc)->timer);
	fr_set_link_state(0, dev);
}