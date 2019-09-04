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
struct uart_port {int line; int regshift; TYPE_2__* dev; int /*<<< orphan*/  serial_in; int /*<<< orphan*/  iotype; int /*<<< orphan*/  serial_out; } ;
struct TYPE_3__ {int /*<<< orphan*/  fn; int /*<<< orphan*/  tx_param; int /*<<< orphan*/  rx_param; } ;
struct dw8250_data {int uart_16550_compatible; TYPE_1__ dma; } ;
struct device_node {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  parent; struct device_node* of_node; } ;

/* Variables and functions */
 int /*<<< orphan*/  IORESOURCE_MEM ; 
 int /*<<< orphan*/  UPIO_MEM32 ; 
 int /*<<< orphan*/  UPIO_MEM32BE ; 
 scalar_t__ acpi_dev_present (char*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  dw8250_idma_filter ; 
 int /*<<< orphan*/  dw8250_serial_in32 ; 
 int /*<<< orphan*/  dw8250_serial_in32be ; 
 int /*<<< orphan*/  dw8250_serial_out32be ; 
 int /*<<< orphan*/  dw8250_serial_out38x ; 
 int of_alias_get_id (struct device_node*,char*) ; 
 scalar_t__ of_device_is_big_endian (struct device_node*) ; 
 scalar_t__ of_device_is_compatible (struct device_node*,char*) ; 
 scalar_t__ platform_get_resource_byname (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  to_platform_device (TYPE_2__*) ; 

__attribute__((used)) static void dw8250_quirks(struct uart_port *p, struct dw8250_data *data)
{
	if (p->dev->of_node) {
		struct device_node *np = p->dev->of_node;
		int id;

		/* get index of serial line, if found in DT aliases */
		id = of_alias_get_id(np, "serial");
		if (id >= 0)
			p->line = id;
#ifdef CONFIG_64BIT
		if (of_device_is_compatible(np, "cavium,octeon-3860-uart")) {
			p->serial_in = dw8250_serial_inq;
			p->serial_out = dw8250_serial_outq;
			p->flags = UPF_SKIP_TEST | UPF_SHARE_IRQ | UPF_FIXED_TYPE;
			p->type = PORT_OCTEON;
			data->usr_reg = 0x27;
			data->skip_autocfg = true;
		}
#endif
		if (of_device_is_big_endian(p->dev->of_node)) {
			p->iotype = UPIO_MEM32BE;
			p->serial_in = dw8250_serial_in32be;
			p->serial_out = dw8250_serial_out32be;
		}
		if (of_device_is_compatible(np, "marvell,armada-38x-uart"))
			p->serial_out = dw8250_serial_out38x;

	} else if (acpi_dev_present("APMC0D08", NULL, -1)) {
		p->iotype = UPIO_MEM32;
		p->regshift = 2;
		p->serial_in = dw8250_serial_in32;
		data->uart_16550_compatible = true;
	}

	/* Platforms with iDMA */
	if (platform_get_resource_byname(to_platform_device(p->dev),
					 IORESOURCE_MEM, "lpss_priv")) {
		data->dma.rx_param = p->dev->parent;
		data->dma.tx_param = p->dev->parent;
		data->dma.fn = dw8250_idma_filter;
	}
}