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
struct TYPE_2__ {int req_issync; int /*<<< orphan*/  done; } ;
struct st95hf_context {TYPE_1__ spicontext; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  IRQ_WAKE_THREAD ; 
 int /*<<< orphan*/  complete (int /*<<< orphan*/ *) ; 

__attribute__((used)) static irqreturn_t st95hf_irq_handler(int irq, void  *st95hfcontext)
{
	struct st95hf_context *stcontext  =
		(struct st95hf_context *)st95hfcontext;

	if (stcontext->spicontext.req_issync) {
		complete(&stcontext->spicontext.done);
		stcontext->spicontext.req_issync = false;
		return IRQ_HANDLED;
	}

	return IRQ_WAKE_THREAD;
}