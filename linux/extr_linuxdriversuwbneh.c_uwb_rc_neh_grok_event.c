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
struct uwb_rceb {scalar_t__ bEventContext; int /*<<< orphan*/  wEvent; int /*<<< orphan*/  bEventType; } ;
struct uwb_rc_neh {int completed; int /*<<< orphan*/  timer; } ;
struct device {int dummy; } ;
struct TYPE_2__ {struct device dev; } ;
struct uwb_rc {int /*<<< orphan*/  neh_lock; TYPE_1__ uwb_dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  del_timer (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,size_t) ; 
 int /*<<< orphan*/  dev_warn (struct device*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,size_t) ; 
 struct uwb_rceb* kmalloc (size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  le16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (struct uwb_rceb*,struct uwb_rceb*,size_t) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  uwb_rc_neh_cb (struct uwb_rc_neh*,struct uwb_rceb*,size_t) ; 
 struct uwb_rc_neh* uwb_rc_neh_lookup (struct uwb_rc*,struct uwb_rceb*) ; 
 int /*<<< orphan*/  uwb_rc_notif (struct uwb_rc*,struct uwb_rceb*,size_t) ; 

__attribute__((used)) static void uwb_rc_neh_grok_event(struct uwb_rc *rc, struct uwb_rceb *rceb, size_t size)
{
	struct device *dev = &rc->uwb_dev.dev;
	struct uwb_rc_neh *neh;
	struct uwb_rceb *notif;
	unsigned long flags;

	if (rceb->bEventContext == 0) {
		notif = kmalloc(size, GFP_ATOMIC);
		if (notif) {
			memcpy(notif, rceb, size);
			uwb_rc_notif(rc, notif, size);
		} else
			dev_err(dev, "event 0x%02x/%04x/%02x (%zu bytes): no memory\n",
				rceb->bEventType, le16_to_cpu(rceb->wEvent),
				rceb->bEventContext, size);
	} else {
		neh = uwb_rc_neh_lookup(rc, rceb);
		if (neh) {
			spin_lock_irqsave(&rc->neh_lock, flags);
			/* to guard against a timeout */
			neh->completed = 1;
			del_timer(&neh->timer);
			spin_unlock_irqrestore(&rc->neh_lock, flags);
			uwb_rc_neh_cb(neh, rceb, size);
		} else
			dev_warn(dev, "event 0x%02x/%04x/%02x (%zu bytes): nobody cared\n",
				 rceb->bEventType, le16_to_cpu(rceb->wEvent),
				 rceb->bEventContext, size);
	}
}