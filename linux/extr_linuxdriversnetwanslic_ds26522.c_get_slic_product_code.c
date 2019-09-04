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
typedef  int u8 ;
struct spi_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DS26522_IDR_ADDR ; 
 int slic_read (struct spi_device*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool get_slic_product_code(struct spi_device *spi)
{
	u8 device_id;

	device_id = slic_read(spi, DS26522_IDR_ADDR);
	if ((device_id & 0xf8) == 0x68)
		return true;
	else
		return false;
}