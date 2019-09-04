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
typedef  int u32 ;
struct stm32_spi {int fifo_size; int cur_bpw; } ;

/* Variables and functions */

__attribute__((used)) static u32 stm32_spi_prepare_fthlv(struct stm32_spi *spi)
{
	u32 fthlv, half_fifo;

	/* data packet should not exceed 1/2 of fifo space */
	half_fifo = (spi->fifo_size / 2);

	if (spi->cur_bpw <= 8)
		fthlv = half_fifo;
	else if (spi->cur_bpw <= 16)
		fthlv = half_fifo / 2;
	else
		fthlv = half_fifo / 4;

	/* align packet size with data registers access */
	if (spi->cur_bpw > 8)
		fthlv -= (fthlv % 2); /* multiple of 2 */
	else
		fthlv -= (fthlv % 4); /* multiple of 4 */

	return fthlv;
}