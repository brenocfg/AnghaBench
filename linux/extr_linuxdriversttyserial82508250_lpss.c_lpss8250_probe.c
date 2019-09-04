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
struct TYPE_2__ {int regshift; int uartclk; int flags; int /*<<< orphan*/  membase; int /*<<< orphan*/  mapbase; int /*<<< orphan*/  iotype; int /*<<< orphan*/  type; struct lpss8250* private_data; int /*<<< orphan*/  irq; int /*<<< orphan*/ * dev; } ;
struct uart_8250_port {int capabilities; TYPE_1__ port; } ;
struct pci_device_id {scalar_t__ driver_data; } ;
struct pci_dev {int /*<<< orphan*/  irq; int /*<<< orphan*/  dev; } ;
struct lpss8250_board {int base_baud; int (* setup ) (struct lpss8250*,TYPE_1__*) ;int /*<<< orphan*/  (* exit ) (struct lpss8250*) ;} ;
struct lpss8250 {int line; struct lpss8250_board* board; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  PORT_16550A ; 
 int UART_CAP_AFE ; 
 int UART_CAP_FIFO ; 
 int UPF_FIXED_PORT ; 
 int UPF_FIXED_TYPE ; 
 int UPF_SHARE_IRQ ; 
 int /*<<< orphan*/  UPIO_MEM ; 
 struct lpss8250* devm_kzalloc (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int lpss8250_dma_setup (struct lpss8250*,struct uart_8250_port*) ; 
 int /*<<< orphan*/  memset (struct uart_8250_port*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pci_resource_start (struct pci_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_set_drvdata (struct pci_dev*,struct lpss8250*) ; 
 int pcim_enable_device (struct pci_dev*) ; 
 int /*<<< orphan*/  pcim_iomap (struct pci_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int serial8250_register_8250_port (struct uart_8250_port*) ; 
 int stub1 (struct lpss8250*,TYPE_1__*) ; 
 int /*<<< orphan*/  stub2 (struct lpss8250*) ; 

__attribute__((used)) static int lpss8250_probe(struct pci_dev *pdev, const struct pci_device_id *id)
{
	struct uart_8250_port uart;
	struct lpss8250 *lpss;
	int ret;

	ret = pcim_enable_device(pdev);
	if (ret)
		return ret;

	lpss = devm_kzalloc(&pdev->dev, sizeof(*lpss), GFP_KERNEL);
	if (!lpss)
		return -ENOMEM;

	lpss->board = (struct lpss8250_board *)id->driver_data;

	memset(&uart, 0, sizeof(struct uart_8250_port));

	uart.port.dev = &pdev->dev;
	uart.port.irq = pdev->irq;
	uart.port.private_data = lpss;
	uart.port.type = PORT_16550A;
	uart.port.iotype = UPIO_MEM;
	uart.port.regshift = 2;
	uart.port.uartclk = lpss->board->base_baud * 16;
	uart.port.flags = UPF_SHARE_IRQ | UPF_FIXED_PORT | UPF_FIXED_TYPE;
	uart.capabilities = UART_CAP_FIFO | UART_CAP_AFE;
	uart.port.mapbase = pci_resource_start(pdev, 0);
	uart.port.membase = pcim_iomap(pdev, 0, 0);
	if (!uart.port.membase)
		return -ENOMEM;

	ret = lpss->board->setup(lpss, &uart.port);
	if (ret)
		return ret;

	ret = lpss8250_dma_setup(lpss, &uart);
	if (ret)
		goto err_exit;

	ret = serial8250_register_8250_port(&uart);
	if (ret < 0)
		goto err_exit;

	lpss->line = ret;

	pci_set_drvdata(pdev, lpss);
	return 0;

err_exit:
	if (lpss->board->exit)
		lpss->board->exit(lpss);
	return ret;
}