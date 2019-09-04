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
struct if_spi_card {int dummy; } ;

/* Variables and functions */
 int IF_SPI_HICT_CMD_DOWNLOAD_OVER_AUTO ; 
 int IF_SPI_HICT_CMD_UPLOAD_OVER_AUTO ; 
 int IF_SPI_HICT_RX_UPLOAD_OVER_AUTO ; 
 int IF_SPI_HICT_TX_DOWNLOAD_OVER_AUTO ; 
 int IF_SPI_HISM_CARDEVENT ; 
 int IF_SPI_HISM_CMD_DOWNLOAD_RDY ; 
 int IF_SPI_HISM_CMD_UPLOAD_RDY ; 
 int IF_SPI_HISM_RX_UPLOAD_RDY ; 
 int IF_SPI_HISM_TX_DOWNLOAD_RDY ; 
 int /*<<< orphan*/  IF_SPI_HOST_INT_CTRL_REG ; 
 int /*<<< orphan*/  IF_SPI_HOST_INT_STATUS_MASK_REG ; 
 int spu_write_u16 (struct if_spi_card*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int spu_set_interrupt_mode(struct if_spi_card *card,
			   int suppress_host_int,
			   int auto_int)
{
	int err = 0;

	/*
	 * We can suppress a host interrupt by clearing the appropriate
	 * bit in the "host interrupt status mask" register
	 */
	if (suppress_host_int) {
		err = spu_write_u16(card, IF_SPI_HOST_INT_STATUS_MASK_REG, 0);
		if (err)
			return err;
	} else {
		err = spu_write_u16(card, IF_SPI_HOST_INT_STATUS_MASK_REG,
			      IF_SPI_HISM_TX_DOWNLOAD_RDY |
			      IF_SPI_HISM_RX_UPLOAD_RDY |
			      IF_SPI_HISM_CMD_DOWNLOAD_RDY |
			      IF_SPI_HISM_CARDEVENT |
			      IF_SPI_HISM_CMD_UPLOAD_RDY);
		if (err)
			return err;
	}

	/*
	 * If auto-interrupts are on, the completion of certain transactions
	 * will trigger an interrupt automatically. If auto-interrupts
	 * are off, we need to set the "Card Interrupt Cause" register to
	 * trigger a card interrupt.
	 */
	if (auto_int) {
		err = spu_write_u16(card, IF_SPI_HOST_INT_CTRL_REG,
				IF_SPI_HICT_TX_DOWNLOAD_OVER_AUTO |
				IF_SPI_HICT_RX_UPLOAD_OVER_AUTO |
				IF_SPI_HICT_CMD_DOWNLOAD_OVER_AUTO |
				IF_SPI_HICT_CMD_UPLOAD_OVER_AUTO);
		if (err)
			return err;
	} else {
		err = spu_write_u16(card, IF_SPI_HOST_INT_STATUS_MASK_REG, 0);
		if (err)
			return err;
	}
	return err;
}