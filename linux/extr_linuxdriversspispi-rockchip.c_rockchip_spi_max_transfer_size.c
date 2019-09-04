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
struct spi_device {int dummy; } ;

/* Variables and functions */
 size_t ROCKCHIP_SPI_MAX_TRANLEN ; 

__attribute__((used)) static size_t rockchip_spi_max_transfer_size(struct spi_device *spi)
{
	return ROCKCHIP_SPI_MAX_TRANLEN;
}