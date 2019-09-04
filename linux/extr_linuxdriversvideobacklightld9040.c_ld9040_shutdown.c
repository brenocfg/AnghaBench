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
struct ld9040 {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  FB_BLANK_POWERDOWN ; 
 int /*<<< orphan*/  ld9040_power (struct ld9040*,int /*<<< orphan*/ ) ; 
 struct ld9040* spi_get_drvdata (struct spi_device*) ; 

__attribute__((used)) static void ld9040_shutdown(struct spi_device *spi)
{
	struct ld9040 *lcd = spi_get_drvdata(spi);

	ld9040_power(lcd, FB_BLANK_POWERDOWN);
}