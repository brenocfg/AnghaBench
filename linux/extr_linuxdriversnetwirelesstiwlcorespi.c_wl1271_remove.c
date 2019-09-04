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
struct wl12xx_spi_glue {int /*<<< orphan*/  core; } ;
struct spi_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  platform_device_unregister (int /*<<< orphan*/ ) ; 
 struct wl12xx_spi_glue* spi_get_drvdata (struct spi_device*) ; 

__attribute__((used)) static int wl1271_remove(struct spi_device *spi)
{
	struct wl12xx_spi_glue *glue = spi_get_drvdata(spi);

	platform_device_unregister(glue->core);

	return 0;
}