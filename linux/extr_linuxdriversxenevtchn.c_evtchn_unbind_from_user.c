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
struct user_evtchn {int /*<<< orphan*/  port; } ;
struct per_user_data {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  del_evtchn (struct per_user_data*,struct user_evtchn*) ; 
 int irq_from_evtchn (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  unbind_from_irqhandler (int,struct user_evtchn*) ; 

__attribute__((used)) static void evtchn_unbind_from_user(struct per_user_data *u,
				    struct user_evtchn *evtchn)
{
	int irq = irq_from_evtchn(evtchn->port);

	BUG_ON(irq < 0);

	unbind_from_irqhandler(irq, evtchn);

	del_evtchn(u, evtchn);
}