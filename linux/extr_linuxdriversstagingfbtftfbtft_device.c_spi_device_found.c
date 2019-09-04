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
struct spi_device {int max_speed_hz; int /*<<< orphan*/  mode; int /*<<< orphan*/  bits_per_word; int /*<<< orphan*/  modalias; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_info (struct device*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_name (struct device*) ; 
 struct spi_device* to_spi_device (struct device*) ; 

__attribute__((used)) static int spi_device_found(struct device *dev, void *data)
{
	struct spi_device *spi = to_spi_device(dev);

	dev_info(dev, "%s %s %dkHz %d bits mode=0x%02X\n", spi->modalias,
		 dev_name(dev), spi->max_speed_hz / 1000, spi->bits_per_word,
		 spi->mode);

	return 0;
}