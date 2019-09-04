#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct net_device {int dummy; } ;
typedef  int /*<<< orphan*/  hdlc_device ;
struct TYPE_6__ {scalar_t__ expires; } ;
struct TYPE_5__ {scalar_t__ lmi; } ;
struct TYPE_7__ {int dce_changed; int last_errors; TYPE_2__ timer; struct net_device* dev; scalar_t__ rxseq; scalar_t__ txseq; scalar_t__ n391cnt; scalar_t__ fullrep_sent; scalar_t__ request; scalar_t__ reliable; TYPE_1__ settings; } ;

/* Variables and functions */
 scalar_t__ HZ ; 
 scalar_t__ LMI_NONE ; 
 int /*<<< orphan*/  add_timer (TYPE_2__*) ; 
 int /*<<< orphan*/ * dev_to_hdlc (struct net_device*) ; 
 int /*<<< orphan*/  fr_set_link_state (int,struct net_device*) ; 
 int /*<<< orphan*/  fr_timer ; 
 scalar_t__ jiffies ; 
 TYPE_3__* state (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  timer_setup (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void fr_start(struct net_device *dev)
{
	hdlc_device *hdlc = dev_to_hdlc(dev);
#ifdef DEBUG_LINK
	printk(KERN_DEBUG "fr_start\n");
#endif
	if (state(hdlc)->settings.lmi != LMI_NONE) {
		state(hdlc)->reliable = 0;
		state(hdlc)->dce_changed = 1;
		state(hdlc)->request = 0;
		state(hdlc)->fullrep_sent = 0;
		state(hdlc)->last_errors = 0xFFFFFFFF;
		state(hdlc)->n391cnt = 0;
		state(hdlc)->txseq = state(hdlc)->rxseq = 0;

		state(hdlc)->dev = dev;
		timer_setup(&state(hdlc)->timer, fr_timer, 0);
		/* First poll after 1 s */
		state(hdlc)->timer.expires = jiffies + HZ;
		add_timer(&state(hdlc)->timer);
	} else
		fr_set_link_state(1, dev);
}