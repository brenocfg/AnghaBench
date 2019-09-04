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
struct uwb_rc_neh {scalar_t__ context; scalar_t__ completed; struct uwb_rc* rc; } ;
struct uwb_rc {int /*<<< orphan*/  neh_lock; } ;
struct timer_list {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ETIMEDOUT ; 
 int /*<<< orphan*/  __uwb_rc_neh_rm (struct uwb_rc*,struct uwb_rc_neh*) ; 
 struct uwb_rc_neh* from_timer (int /*<<< orphan*/ ,struct timer_list*,int /*<<< orphan*/ ) ; 
 struct uwb_rc_neh* neh ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  timer ; 
 int /*<<< orphan*/  uwb_rc_neh_cb (struct uwb_rc_neh*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void uwb_rc_neh_timer(struct timer_list *t)
{
	struct uwb_rc_neh *neh = from_timer(neh, t, timer);
	struct uwb_rc *rc = neh->rc;
	unsigned long flags;

	spin_lock_irqsave(&rc->neh_lock, flags);
	if (neh->completed) {
		spin_unlock_irqrestore(&rc->neh_lock, flags);
		return;
	}
	if (neh->context)
		__uwb_rc_neh_rm(rc, neh);
	else
		neh = NULL;
	spin_unlock_irqrestore(&rc->neh_lock, flags);

	if (neh)
		uwb_rc_neh_cb(neh, NULL, -ETIMEDOUT);
}