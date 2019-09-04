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
typedef  int u32 ;
struct uart_port {int /*<<< orphan*/  irq; int /*<<< orphan*/  dev; } ;
struct stm32_usart_offsets {int /*<<< orphan*/  cr1; } ;
struct stm32_usart_config {scalar_t__ has_wakeup; } ;
struct stm32_port {scalar_t__ wakeirq; scalar_t__ fifoen; TYPE_1__* info; } ;
struct TYPE_4__ {char* name; } ;
struct TYPE_3__ {struct stm32_usart_config cfg; struct stm32_usart_offsets ofs; } ;

/* Variables and functions */
 int /*<<< orphan*/  IRQF_NO_SUSPEND ; 
 int USART_CR1_FIFOEN ; 
 int USART_CR1_RE ; 
 int USART_CR1_RXNEIE ; 
 int USART_CR1_TE ; 
 int dev_pm_set_dedicated_wake_irq (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,struct uart_port*) ; 
 int request_threaded_irq (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char const*,struct uart_port*) ; 
 int /*<<< orphan*/  stm32_interrupt ; 
 int /*<<< orphan*/  stm32_set_bits (struct uart_port*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stm32_threaded_interrupt ; 
 TYPE_2__* to_platform_device (int /*<<< orphan*/ ) ; 
 struct stm32_port* to_stm32_port (struct uart_port*) ; 

__attribute__((used)) static int stm32_startup(struct uart_port *port)
{
	struct stm32_port *stm32_port = to_stm32_port(port);
	struct stm32_usart_offsets *ofs = &stm32_port->info->ofs;
	struct stm32_usart_config *cfg = &stm32_port->info->cfg;
	const char *name = to_platform_device(port->dev)->name;
	u32 val;
	int ret;

	ret = request_threaded_irq(port->irq, stm32_interrupt,
				   stm32_threaded_interrupt,
				   IRQF_NO_SUSPEND, name, port);
	if (ret)
		return ret;

	if (cfg->has_wakeup && stm32_port->wakeirq >= 0) {
		ret = dev_pm_set_dedicated_wake_irq(port->dev,
						    stm32_port->wakeirq);
		if (ret) {
			free_irq(port->irq, port);
			return ret;
		}
	}

	val = USART_CR1_RXNEIE | USART_CR1_TE | USART_CR1_RE;
	if (stm32_port->fifoen)
		val |= USART_CR1_FIFOEN;
	stm32_set_bits(port, ofs->cr1, val);

	return 0;
}