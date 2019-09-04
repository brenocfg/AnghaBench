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
typedef  int u16 ;
struct spi_controller {int /*<<< orphan*/  cur_msg; } ;
struct dw_spi {int /*<<< orphan*/  (* transfer_handler ) (struct dw_spi*) ;} ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  DW_SPI_ISR ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  IRQ_NONE ; 
 int /*<<< orphan*/  SPI_INT_TXEI ; 
 int dw_readl (struct dw_spi*,int /*<<< orphan*/ ) ; 
 struct dw_spi* spi_controller_get_devdata (struct spi_controller*) ; 
 int /*<<< orphan*/  spi_mask_intr (struct dw_spi*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct dw_spi*) ; 

__attribute__((used)) static irqreturn_t dw_spi_irq(int irq, void *dev_id)
{
	struct spi_controller *master = dev_id;
	struct dw_spi *dws = spi_controller_get_devdata(master);
	u16 irq_status = dw_readl(dws, DW_SPI_ISR) & 0x3f;

	if (!irq_status)
		return IRQ_NONE;

	if (!master->cur_msg) {
		spi_mask_intr(dws, SPI_INT_TXEI);
		return IRQ_HANDLED;
	}

	return dws->transfer_handler(dws);
}