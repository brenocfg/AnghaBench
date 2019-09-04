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
struct rt1711h_chip {int /*<<< orphan*/  dev; } ;
struct i2c_client {int /*<<< orphan*/  irq; } ;

/* Variables and functions */
 int IRQF_ONESHOT ; 
 int IRQF_TRIGGER_LOW ; 
 int /*<<< orphan*/  TCPC_ALERT_MASK ; 
 int /*<<< orphan*/  dev_name (int /*<<< orphan*/ ) ; 
 int devm_request_threaded_irq (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,struct rt1711h_chip*) ; 
 int /*<<< orphan*/  enable_irq_wake (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rt1711h_irq ; 
 int rt1711h_write16 (struct rt1711h_chip*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int rt1711h_init_alert(struct rt1711h_chip *chip,
			      struct i2c_client *client)
{
	int ret;

	/* Disable chip interrupts before requesting irq */
	ret = rt1711h_write16(chip, TCPC_ALERT_MASK, 0);
	if (ret < 0)
		return ret;

	ret = devm_request_threaded_irq(chip->dev, client->irq, NULL,
					rt1711h_irq,
					IRQF_ONESHOT | IRQF_TRIGGER_LOW,
					dev_name(chip->dev), chip);
	if (ret < 0)
		return ret;
	enable_irq_wake(client->irq);
	return 0;
}