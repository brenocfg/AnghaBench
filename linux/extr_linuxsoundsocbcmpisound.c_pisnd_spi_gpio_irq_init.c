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
struct device {int dummy; } ;

/* Variables and functions */
 int IRQF_ONESHOT ; 
 int IRQF_TIMER ; 
 int IRQF_TRIGGER_RISING ; 
 int /*<<< orphan*/  data_available ; 
 int /*<<< orphan*/  data_available_interrupt_handler ; 
 int /*<<< orphan*/  gpiod_to_irq (int /*<<< orphan*/ ) ; 
 int request_threaded_irq (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,char*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int pisnd_spi_gpio_irq_init(struct device *dev)
{
	return request_threaded_irq(
		gpiod_to_irq(data_available), NULL,
		data_available_interrupt_handler,
		IRQF_TIMER | IRQF_TRIGGER_RISING | IRQF_ONESHOT,
		"data_available_int",
		NULL
		);
}