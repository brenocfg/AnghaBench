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
struct tle62x0_state {int nr_gpio; } ;
struct spi_device {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_attr_status_show ; 
 int /*<<< orphan*/  device_remove_file (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ ** gpio_attrs ; 
 int /*<<< orphan*/  kfree (struct tle62x0_state*) ; 
 struct tle62x0_state* spi_get_drvdata (struct spi_device*) ; 

__attribute__((used)) static int tle62x0_remove(struct spi_device *spi)
{
	struct tle62x0_state *st = spi_get_drvdata(spi);
	int ptr;

	for (ptr = 0; ptr < st->nr_gpio; ptr++)
		device_remove_file(&spi->dev, gpio_attrs[ptr]);

	device_remove_file(&spi->dev, &dev_attr_status_show);
	kfree(st);
	return 0;
}