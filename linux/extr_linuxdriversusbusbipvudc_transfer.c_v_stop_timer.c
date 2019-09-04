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
struct transfer_timer {int /*<<< orphan*/  state; } ;
struct vudc {TYPE_1__* pdev; struct transfer_timer tr_timer; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  VUDC_TR_STOPPED ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*) ; 

void v_stop_timer(struct vudc *udc)
{
	struct transfer_timer *t = &udc->tr_timer;

	/* timer itself will take care of stopping */
	dev_dbg(&udc->pdev->dev, "timer stop");
	t->state = VUDC_TR_STOPPED;
}