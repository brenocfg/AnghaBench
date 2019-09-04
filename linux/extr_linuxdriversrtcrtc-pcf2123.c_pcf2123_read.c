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
typedef  int /*<<< orphan*/  u8 ;
struct spi_device {int dummy; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  PCF2123_READ ; 
 int /*<<< orphan*/  pcf2123_delay_trec () ; 
 int spi_write_then_read (struct spi_device*,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,size_t) ; 
 struct spi_device* to_spi_device (struct device*) ; 

__attribute__((used)) static int pcf2123_read(struct device *dev, u8 reg, u8 *rxbuf, size_t size)
{
	struct spi_device *spi = to_spi_device(dev);
	int ret;

	reg |= PCF2123_READ;
	ret = spi_write_then_read(spi, &reg, 1, rxbuf, size);
	pcf2123_delay_trec();

	return ret;
}