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
struct TYPE_2__ {int /*<<< orphan*/ * complete; } ;
struct mrf24j40 {int* rx_buf; TYPE_1__ rx_msg; int /*<<< orphan*/  spi; } ;

/* Variables and functions */
 int MRF24J40_WRITESHORT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  REG_BBREG1 ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  printdev (struct mrf24j40*) ; 
 int spi_async (int /*<<< orphan*/ ,TYPE_1__*) ; 

__attribute__((used)) static void mrf24j40_handle_rx_read_buf_unlock(struct mrf24j40 *devrec)
{
	int ret;

	/* Turn back on reception of packets off the air. */
	devrec->rx_msg.complete = NULL;
	devrec->rx_buf[0] = MRF24J40_WRITESHORT(REG_BBREG1);
	devrec->rx_buf[1] = 0x00; /* CLR RXDECINV */
	ret = spi_async(devrec->spi, &devrec->rx_msg);
	if (ret)
		dev_err(printdev(devrec), "failed to unlock rx buffer\n");
}