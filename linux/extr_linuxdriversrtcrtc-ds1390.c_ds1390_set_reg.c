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
 int /*<<< orphan*/  spi_write (struct spi_device*,unsigned char*,int) ; 
 struct spi_device* to_spi_device (struct device*) ; 

__attribute__((used)) static void ds1390_set_reg(struct device *dev, unsigned char address,
			   unsigned char data)
{
	struct spi_device *spi = to_spi_device(dev);
	unsigned char buf[2];

	/* MSB must be '1' to write */
	buf[0] = address | 0x80;
	buf[1] = data;

	spi_write(spi, buf, 2);
}