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
struct lms501kf03 {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  FB_BLANK_POWERDOWN ; 
 int /*<<< orphan*/  lms501kf03_power (struct lms501kf03*,int /*<<< orphan*/ ) ; 
 struct lms501kf03* spi_get_drvdata (struct spi_device*) ; 

__attribute__((used)) static int lms501kf03_remove(struct spi_device *spi)
{
	struct lms501kf03 *lcd = spi_get_drvdata(spi);

	lms501kf03_power(lcd, FB_BLANK_POWERDOWN);
	return 0;
}