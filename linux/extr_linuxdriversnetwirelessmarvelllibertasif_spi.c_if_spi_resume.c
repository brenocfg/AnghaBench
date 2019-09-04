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
struct if_spi_card {int /*<<< orphan*/  resume_work; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  schedule_work (int /*<<< orphan*/ *) ; 
 struct if_spi_card* spi_get_drvdata (struct spi_device*) ; 
 struct spi_device* to_spi_device (struct device*) ; 

__attribute__((used)) static int if_spi_resume(struct device *dev)
{
	struct spi_device *spi = to_spi_device(dev);
	struct if_spi_card *card = spi_get_drvdata(spi);

	/* Schedule delayed work */
	schedule_work(&card->resume_work);

	return 0;
}