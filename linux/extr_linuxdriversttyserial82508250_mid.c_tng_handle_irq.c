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
typedef  int /*<<< orphan*/  u32 ;
struct uart_port {struct mid8250* private_data; } ;
struct uart_8250_port {int dummy; } ;
struct mid8250 {int dma_index; int /*<<< orphan*/  dma_dev; } ;
struct hsu_dma_chip {int dummy; } ;

/* Variables and functions */
 int IRQ_RETVAL (int) ; 
 int /*<<< orphan*/  UART_IIR ; 
 int hsu_dma_do_irq (struct hsu_dma_chip*,int,int /*<<< orphan*/ ) ; 
 int hsu_dma_get_status (struct hsu_dma_chip*,int,int /*<<< orphan*/ *) ; 
 struct hsu_dma_chip* pci_get_drvdata (int /*<<< orphan*/ ) ; 
 int serial8250_handle_irq (struct uart_port*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  serial8250_rx_dma_flush (struct uart_8250_port*) ; 
 int /*<<< orphan*/  serial_port_in (struct uart_port*,int /*<<< orphan*/ ) ; 
 struct uart_8250_port* up_to_u8250p (struct uart_port*) ; 

__attribute__((used)) static int tng_handle_irq(struct uart_port *p)
{
	struct mid8250 *mid = p->private_data;
	struct uart_8250_port *up = up_to_u8250p(p);
	struct hsu_dma_chip *chip;
	u32 status;
	int ret = 0;
	int err;

	chip = pci_get_drvdata(mid->dma_dev);

	/* Rx DMA */
	err = hsu_dma_get_status(chip, mid->dma_index * 2 + 1, &status);
	if (err > 0) {
		serial8250_rx_dma_flush(up);
		ret |= 1;
	} else if (err == 0)
		ret |= hsu_dma_do_irq(chip, mid->dma_index * 2 + 1, status);

	/* Tx DMA */
	err = hsu_dma_get_status(chip, mid->dma_index * 2, &status);
	if (err > 0)
		ret |= 1;
	else if (err == 0)
		ret |= hsu_dma_do_irq(chip, mid->dma_index * 2, status);

	/* UART */
	ret |= serial8250_handle_irq(p, serial_port_in(p, UART_IIR));
	return IRQ_RETVAL(ret);
}