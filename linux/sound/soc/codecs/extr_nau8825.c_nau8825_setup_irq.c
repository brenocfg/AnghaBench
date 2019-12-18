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
struct nau8825 {int /*<<< orphan*/  irq; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int IRQF_ONESHOT ; 
 int IRQF_TRIGGER_LOW ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int) ; 
 int devm_request_threaded_irq (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,char*,struct nau8825*) ; 
 int /*<<< orphan*/  nau8825_interrupt ; 

__attribute__((used)) static int nau8825_setup_irq(struct nau8825 *nau8825)
{
	int ret;

	ret = devm_request_threaded_irq(nau8825->dev, nau8825->irq, NULL,
		nau8825_interrupt, IRQF_TRIGGER_LOW | IRQF_ONESHOT,
		"nau8825", nau8825);

	if (ret) {
		dev_err(nau8825->dev, "Cannot request irq %d (%d)\n",
			nau8825->irq, ret);
		return ret;
	}

	return 0;
}