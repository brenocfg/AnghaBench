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
struct smcd_event {int dummy; } ;
struct smcd_dev {int /*<<< orphan*/  event_wq; } ;
struct smc_ism_event_work {int /*<<< orphan*/  work; struct smcd_event event; struct smcd_dev* smcd; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  INIT_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct smc_ism_event_work* kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  queue_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  smc_ism_event_work ; 

void smcd_handle_event(struct smcd_dev *smcd, struct smcd_event *event)
{
	struct smc_ism_event_work *wrk;

	/* copy event to event work queue, and let it be handled there */
	wrk = kmalloc(sizeof(*wrk), GFP_ATOMIC);
	if (!wrk)
		return;
	INIT_WORK(&wrk->work, smc_ism_event_work);
	wrk->smcd = smcd;
	wrk->event = *event;
	queue_work(smcd->event_wq, &wrk->work);
}