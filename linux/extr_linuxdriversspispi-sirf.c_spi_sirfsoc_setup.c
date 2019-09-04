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
struct spi_device {int cs_gpio; int /*<<< orphan*/  dev; int /*<<< orphan*/  master; } ;
struct sirfsoc_spi {int hw_cs; } ;

/* Variables and functions */
 int /*<<< orphan*/  BITBANG_CS_INACTIVE ; 
 int /*<<< orphan*/  DRIVER_NAME ; 
 int ENOENT ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int gpio_is_valid (int) ; 
 int gpio_request (int,int /*<<< orphan*/ ) ; 
 void* kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spi_get_ctldata (struct spi_device*) ; 
 struct sirfsoc_spi* spi_master_get_devdata (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spi_set_ctldata (struct spi_device*,void*) ; 
 int /*<<< orphan*/  spi_sirfsoc_chipselect (struct spi_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spi_sirfsoc_config_mode (struct spi_device*) ; 

__attribute__((used)) static int spi_sirfsoc_setup(struct spi_device *spi)
{
	struct sirfsoc_spi *sspi;
	int ret = 0;

	sspi = spi_master_get_devdata(spi->master);
	if (spi->cs_gpio == -ENOENT)
		sspi->hw_cs = true;
	else {
		sspi->hw_cs = false;
		if (!spi_get_ctldata(spi)) {
			void *cs = kmalloc(sizeof(int), GFP_KERNEL);
			if (!cs) {
				ret = -ENOMEM;
				goto exit;
			}
			ret = gpio_is_valid(spi->cs_gpio);
			if (!ret) {
				dev_err(&spi->dev, "no valid gpio\n");
				ret = -ENOENT;
				goto exit;
			}
			ret = gpio_request(spi->cs_gpio, DRIVER_NAME);
			if (ret) {
				dev_err(&spi->dev, "failed to request gpio\n");
				goto exit;
			}
			spi_set_ctldata(spi, cs);
		}
	}
	spi_sirfsoc_config_mode(spi);
	spi_sirfsoc_chipselect(spi, BITBANG_CS_INACTIVE);
exit:
	return ret;
}