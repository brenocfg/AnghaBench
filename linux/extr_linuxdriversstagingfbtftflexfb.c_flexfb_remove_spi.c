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
struct fb_info {int dummy; } ;

/* Variables and functions */
 int flexfb_remove_common (int /*<<< orphan*/ *,struct fb_info*) ; 
 struct fb_info* spi_get_drvdata (struct spi_device*) ; 

__attribute__((used)) static int flexfb_remove_spi(struct spi_device *spi)
{
	struct fb_info *info = spi_get_drvdata(spi);

	return flexfb_remove_common(&spi->dev, info);
}