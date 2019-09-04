#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct spi_device {int /*<<< orphan*/  dev; } ;
struct pcf2123_plat_data {TYPE_1__* regs; } ;
struct TYPE_2__ {int /*<<< orphan*/  attr; scalar_t__* name; } ;

/* Variables and functions */
 struct pcf2123_plat_data* dev_get_platdata (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  device_remove_file (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int pcf2123_remove(struct spi_device *spi)
{
	struct pcf2123_plat_data *pdata = dev_get_platdata(&spi->dev);
	int i;

	if (pdata) {
		for (i = 0; i < 16; i++)
			if (pdata->regs[i].name[0])
				device_remove_file(&spi->dev,
						   &pdata->regs[i].attr);
	}

	return 0;
}