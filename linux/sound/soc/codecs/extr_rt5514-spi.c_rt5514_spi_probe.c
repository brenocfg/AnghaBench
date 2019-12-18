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

/* Variables and functions */
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int devm_snd_soc_register_component (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 struct spi_device* rt5514_spi ; 
 int /*<<< orphan*/  rt5514_spi_component ; 
 int /*<<< orphan*/  rt5514_spi_dai ; 

__attribute__((used)) static int rt5514_spi_probe(struct spi_device *spi)
{
	int ret;

	rt5514_spi = spi;

	ret = devm_snd_soc_register_component(&spi->dev,
					      &rt5514_spi_component,
					      &rt5514_spi_dai, 1);
	if (ret < 0) {
		dev_err(&spi->dev, "Failed to register component.\n");
		return ret;
	}

	return 0;
}