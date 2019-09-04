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
struct visorhba_devdata {int /*<<< orphan*/  privlock; TYPE_1__* pending; } ;
struct TYPE_2__ {int /*<<< orphan*/ * sent; scalar_t__ cmdtype; } ;

/* Variables and functions */
 int MAX_PENDING_REQUESTS ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void *del_scsipending_ent(struct visorhba_devdata *devdata, int del)
{
	unsigned long flags;
	void *sent;

	if (del >= MAX_PENDING_REQUESTS)
		return NULL;

	spin_lock_irqsave(&devdata->privlock, flags);
	sent = devdata->pending[del].sent;
	devdata->pending[del].cmdtype = 0;
	devdata->pending[del].sent = NULL;
	spin_unlock_irqrestore(&devdata->privlock, flags);

	return sent;
}