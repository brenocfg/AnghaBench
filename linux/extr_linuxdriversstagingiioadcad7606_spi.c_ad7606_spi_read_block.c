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
struct spi_device {int /*<<< orphan*/  dev; } ;
struct device {int dummy; } ;
typedef  int /*<<< orphan*/  __be16 ;

/* Variables and functions */
 unsigned short be16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int spi_read (struct spi_device*,void*,int) ; 
 struct spi_device* to_spi_device (struct device*) ; 

__attribute__((used)) static int ad7606_spi_read_block(struct device *dev,
				 int count, void *buf)
{
	struct spi_device *spi = to_spi_device(dev);
	int i, ret;
	unsigned short *data = buf;
	__be16 *bdata = buf;

	ret = spi_read(spi, buf, count * 2);
	if (ret < 0) {
		dev_err(&spi->dev, "SPI read error\n");
		return ret;
	}

	for (i = 0; i < count; i++)
		data[i] = be16_to_cpu(bdata[i]);

	return 0;
}