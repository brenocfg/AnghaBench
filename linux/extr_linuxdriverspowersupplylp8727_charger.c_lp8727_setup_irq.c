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
struct lp8727_chg {int irq; int /*<<< orphan*/  debounce_jiffies; int /*<<< orphan*/  dev; int /*<<< orphan*/  work; TYPE_2__* pdata; TYPE_1__* client; } ;
struct TYPE_4__ {unsigned int debounce_msec; } ;
struct TYPE_3__ {int irq; } ;

/* Variables and functions */
 unsigned int DEFAULT_DEBOUNCE_MSEC ; 
 int /*<<< orphan*/  INIT_DELAYED_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int IRQF_ONESHOT ; 
 int IRQF_TRIGGER_FALLING ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  lp8727_delayed_func ; 
 int /*<<< orphan*/  lp8727_isr_func ; 
 int /*<<< orphan*/  msecs_to_jiffies (unsigned int) ; 
 int request_threaded_irq (int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,char*,struct lp8727_chg*) ; 

__attribute__((used)) static int lp8727_setup_irq(struct lp8727_chg *pchg)
{
	int ret;
	int irq = pchg->client->irq;
	unsigned delay_msec = pchg->pdata ? pchg->pdata->debounce_msec :
						DEFAULT_DEBOUNCE_MSEC;

	INIT_DELAYED_WORK(&pchg->work, lp8727_delayed_func);

	if (irq <= 0) {
		dev_warn(pchg->dev, "invalid irq number: %d\n", irq);
		return 0;
	}

	ret = request_threaded_irq(irq,	NULL, lp8727_isr_func,
				IRQF_TRIGGER_FALLING | IRQF_ONESHOT,
				"lp8727_irq", pchg);

	if (ret)
		return ret;

	pchg->irq = irq;
	pchg->debounce_jiffies = msecs_to_jiffies(delay_msec);

	return 0;
}