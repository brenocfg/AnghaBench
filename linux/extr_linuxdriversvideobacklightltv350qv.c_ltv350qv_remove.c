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
struct ltv350qv {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  FB_BLANK_POWERDOWN ; 
 int /*<<< orphan*/  ltv350qv_power (struct ltv350qv*,int /*<<< orphan*/ ) ; 
 struct ltv350qv* spi_get_drvdata (struct spi_device*) ; 

__attribute__((used)) static int ltv350qv_remove(struct spi_device *spi)
{
	struct ltv350qv *lcd = spi_get_drvdata(spi);

	ltv350qv_power(lcd, FB_BLANK_POWERDOWN);
	return 0;
}