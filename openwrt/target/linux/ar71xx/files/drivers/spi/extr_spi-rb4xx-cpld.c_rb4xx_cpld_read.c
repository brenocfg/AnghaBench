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
struct spi_transfer {unsigned char const** tx_buf; int len; unsigned char* rx_buf; } ;
struct spi_message {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  spi; } ;

/* Variables and functions */
#define  CPLD_CMD_READ_NAND 128 
 int ENODEV ; 
 TYPE_1__* rb4xx_cpld ; 
 int /*<<< orphan*/  spi_message_add_tail (struct spi_transfer*,struct spi_message*) ; 
 int /*<<< orphan*/  spi_message_init (struct spi_message*) ; 
 int spi_sync (int /*<<< orphan*/ ,struct spi_message*) ; 

int rb4xx_cpld_read(unsigned char *rx_buf, unsigned count)
{
	static const unsigned char cmd[2] = { CPLD_CMD_READ_NAND, 0 };
	struct spi_transfer t[2] = {
		{
			.tx_buf = &cmd,
			.len = 2,
		}, {
			.rx_buf = rx_buf,
			.len = count,
		},
	};
	struct spi_message m;

	if (rb4xx_cpld == NULL)
		return -ENODEV;

	spi_message_init(&m);
	spi_message_add_tail(&t[0], &m);
	spi_message_add_tail(&t[1], &m);
	return spi_sync(rb4xx_cpld->spi, &m);
}