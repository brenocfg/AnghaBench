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
struct ctlr_info {int /*<<< orphan*/  resubmit_wq; } ;
struct CommandList {int /*<<< orphan*/  work; } ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hpsa_command_resubmit_worker ; 
 int /*<<< orphan*/  queue_work_on (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  raw_smp_processor_id () ; 

__attribute__((used)) static void hpsa_retry_cmd(struct ctlr_info *h, struct CommandList *c)
{
	INIT_WORK(&c->work, hpsa_command_resubmit_worker);
	queue_work_on(raw_smp_processor_id(), h->resubmit_wq, &c->work);
}