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
typedef  scalar_t__ u8 ;
struct uart_port {int /*<<< orphan*/  dev; scalar_t__ iobase; } ;
struct spi_transfer {int len; scalar_t__* rx_buf; scalar_t__** tx_buf; } ;
typedef  int /*<<< orphan*/  header ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (struct spi_transfer*) ; 
 scalar_t__ MAX310X_RHR_REG ; 
 int /*<<< orphan*/  spi_sync_transfer (int /*<<< orphan*/ ,struct spi_transfer*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  to_spi_device (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void max310x_batch_read(struct uart_port *port, u8 *rxbuf, unsigned int len)
{
	u8 header[] = { port->iobase + MAX310X_RHR_REG };
	struct spi_transfer xfer[] = {
		{
			.tx_buf = &header,
			.len = sizeof(header),
		}, {
			.rx_buf = rxbuf,
			.len = len,
		}
	};
	spi_sync_transfer(to_spi_device(port->dev), xfer, ARRAY_SIZE(xfer));
}