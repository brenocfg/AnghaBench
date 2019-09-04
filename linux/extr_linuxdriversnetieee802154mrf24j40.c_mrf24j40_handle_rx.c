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
struct TYPE_4__ {int /*<<< orphan*/  complete; } ;
struct TYPE_3__ {int len; } ;
struct mrf24j40 {TYPE_2__ rx_msg; int /*<<< orphan*/  spi; int /*<<< orphan*/ * rx_buf; TYPE_1__ rx_trx; } ;

/* Variables and functions */
 int /*<<< orphan*/  BIT_RXDECINV ; 
 int /*<<< orphan*/  MRF24J40_WRITESHORT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  REG_BBREG1 ; 
 int /*<<< orphan*/  mrf24j40_handle_rx_read_len ; 
 int spi_async (int /*<<< orphan*/ ,TYPE_2__*) ; 

__attribute__((used)) static int mrf24j40_handle_rx(struct mrf24j40 *devrec)
{
	/* Turn off reception of packets off the air. This prevents the
	 * device from overwriting the buffer while we're reading it.
	 */
	devrec->rx_msg.complete = mrf24j40_handle_rx_read_len;
	devrec->rx_trx.len = 2;
	devrec->rx_buf[0] = MRF24J40_WRITESHORT(REG_BBREG1);
	devrec->rx_buf[1] = BIT_RXDECINV; /* SET RXDECINV */

	return spi_async(devrec->spi, &devrec->rx_msg);
}