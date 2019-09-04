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
struct sk_buff {int dummy; } ;
struct nfcmrvl_spi_drv_data {TYPE_1__* spi; int /*<<< orphan*/  priv; int /*<<< orphan*/  nci_spi; int /*<<< orphan*/  handshake_completion; int /*<<< orphan*/  flags; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  SPI_WAIT_HANDSHAKE ; 
 int /*<<< orphan*/  complete (int /*<<< orphan*/ *) ; 
 struct sk_buff* nci_spi_read (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nfc_err (int /*<<< orphan*/ *,char*) ; 
 scalar_t__ nfcmrvl_nci_recv_frame (int /*<<< orphan*/ ,struct sk_buff*) ; 
 scalar_t__ test_and_clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static irqreturn_t nfcmrvl_spi_int_irq_thread_fn(int irq, void *drv_data_ptr)
{
	struct nfcmrvl_spi_drv_data *drv_data = drv_data_ptr;
	struct sk_buff *skb;

	/*
	 * Special case where we are waiting for SPI_INT deassertion to start a
	 * transfer.
	 */
	if (test_and_clear_bit(SPI_WAIT_HANDSHAKE, &drv_data->flags)) {
		complete(&drv_data->handshake_completion);
		return IRQ_HANDLED;
	}

	/* Normal case, SPI_INT deasserted by slave to trigger a master read */

	skb = nci_spi_read(drv_data->nci_spi);
	if (!skb) {
		nfc_err(&drv_data->spi->dev, "failed to read spi packet");
		return IRQ_HANDLED;
	}

	if (nfcmrvl_nci_recv_frame(drv_data->priv, skb) < 0)
		nfc_err(&drv_data->spi->dev, "corrupted RX packet");

	return IRQ_HANDLED;
}