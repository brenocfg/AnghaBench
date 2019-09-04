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
 int spi_write_then_read (struct spi_device*,unsigned char*,int,unsigned char*,int) ; 
 struct spi_device* to_spi_device (struct device*) ; 

__attribute__((used)) static int rx4581_get_reg(struct device *dev, unsigned char address,
				unsigned char *data)
{
	struct spi_device *spi = to_spi_device(dev);

	/* Set MSB to indicate read */
	*data = address | 0x80;

	return spi_write_then_read(spi, data, 1, data, 1);
}