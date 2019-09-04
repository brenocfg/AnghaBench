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
struct spi_board_info {int dummy; } ;

/* Variables and functions */
 int spi_register_board_info (struct spi_board_info*,int) ; 

__attribute__((used)) static int fbtft_device_spi_device_register(struct spi_board_info *spi)
{
	return spi_register_board_info(spi, 1);
}