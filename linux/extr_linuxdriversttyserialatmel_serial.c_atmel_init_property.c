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
struct TYPE_2__ {struct device_node* of_node; } ;
struct platform_device {TYPE_1__ dev; } ;
struct device_node {int dummy; } ;
struct atmel_uart_port {int use_dma_rx; int use_pdc_rx; int use_dma_tx; int use_pdc_tx; } ;

/* Variables and functions */
 scalar_t__ of_property_read_bool (struct device_node*,char*) ; 

__attribute__((used)) static void atmel_init_property(struct atmel_uart_port *atmel_port,
				struct platform_device *pdev)
{
	struct device_node *np = pdev->dev.of_node;

	/* DMA/PDC usage specification */
	if (of_property_read_bool(np, "atmel,use-dma-rx")) {
		if (of_property_read_bool(np, "dmas")) {
			atmel_port->use_dma_rx  = true;
			atmel_port->use_pdc_rx  = false;
		} else {
			atmel_port->use_dma_rx  = false;
			atmel_port->use_pdc_rx  = true;
		}
	} else {
		atmel_port->use_dma_rx  = false;
		atmel_port->use_pdc_rx  = false;
	}

	if (of_property_read_bool(np, "atmel,use-dma-tx")) {
		if (of_property_read_bool(np, "dmas")) {
			atmel_port->use_dma_tx  = true;
			atmel_port->use_pdc_tx  = false;
		} else {
			atmel_port->use_dma_tx  = false;
			atmel_port->use_pdc_tx  = true;
		}
	} else {
		atmel_port->use_dma_tx  = false;
		atmel_port->use_pdc_tx  = false;
	}
}