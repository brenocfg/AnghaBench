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
typedef  int u32 ;
struct uart_port {int /*<<< orphan*/  irq; int /*<<< orphan*/  dev; } ;
struct stm32_usart_offsets {int /*<<< orphan*/  cr1; } ;
struct stm32_usart_config {int /*<<< orphan*/  uart_enable_bit; } ;
struct stm32_port {scalar_t__ fifoen; TYPE_1__* info; } ;
struct TYPE_2__ {struct stm32_usart_config cfg; struct stm32_usart_offsets ofs; } ;

/* Variables and functions */
 int BIT (int /*<<< orphan*/ ) ; 
 int USART_CR1_FIFOEN ; 
 int USART_CR1_RE ; 
 int USART_CR1_RXNEIE ; 
 int USART_CR1_TE ; 
 int USART_CR1_TXEIE ; 
 int /*<<< orphan*/  dev_pm_clear_wake_irq (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,struct uart_port*) ; 
 int /*<<< orphan*/  stm32_clr_bits (struct uart_port*,int /*<<< orphan*/ ,int) ; 
 struct stm32_port* to_stm32_port (struct uart_port*) ; 

__attribute__((used)) static void stm32_shutdown(struct uart_port *port)
{
	struct stm32_port *stm32_port = to_stm32_port(port);
	struct stm32_usart_offsets *ofs = &stm32_port->info->ofs;
	struct stm32_usart_config *cfg = &stm32_port->info->cfg;
	u32 val;

	val = USART_CR1_TXEIE | USART_CR1_RXNEIE | USART_CR1_TE | USART_CR1_RE;
	val |= BIT(cfg->uart_enable_bit);
	if (stm32_port->fifoen)
		val |= USART_CR1_FIFOEN;
	stm32_clr_bits(port, ofs->cr1, val);

	dev_pm_clear_wake_irq(port->dev);
	free_irq(port->irq, port);
}