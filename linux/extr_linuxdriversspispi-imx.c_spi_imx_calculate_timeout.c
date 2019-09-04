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
struct spi_imx_data {int spi_bus_clk; } ;

/* Variables and functions */
 int MSEC_PER_SEC ; 
 int msecs_to_jiffies (int) ; 

__attribute__((used)) static int spi_imx_calculate_timeout(struct spi_imx_data *spi_imx, int size)
{
	unsigned long timeout = 0;

	/* Time with actual data transfer and CS change delay related to HW */
	timeout = (8 + 4) * size / spi_imx->spi_bus_clk;

	/* Add extra second for scheduler related activities */
	timeout += 1;

	/* Double calculated timeout */
	return msecs_to_jiffies(2 * timeout * MSEC_PER_SEC);
}