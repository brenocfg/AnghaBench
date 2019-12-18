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
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  spi_w8r8 (struct spi_device*,int) ; 
 struct spi_device* to_spi_device (struct device*) ; 

__attribute__((used)) static void adau1781_spi_switch_mode(struct device *dev)
{
	struct spi_device *spi = to_spi_device(dev);

	/*
	 * To get the device into SPI mode CLATCH has to be pulled low three
	 * times.  Do this by issuing three dummy reads.
	 */
	spi_w8r8(spi, 0x00);
	spi_w8r8(spi, 0x00);
	spi_w8r8(spi, 0x00);
}