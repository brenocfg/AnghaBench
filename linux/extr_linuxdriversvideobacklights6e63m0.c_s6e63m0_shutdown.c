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
struct s6e63m0 {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  FB_BLANK_POWERDOWN ; 
 int /*<<< orphan*/  s6e63m0_power (struct s6e63m0*,int /*<<< orphan*/ ) ; 
 struct s6e63m0* spi_get_drvdata (struct spi_device*) ; 

__attribute__((used)) static void s6e63m0_shutdown(struct spi_device *spi)
{
	struct s6e63m0 *lcd = spi_get_drvdata(spi);

	s6e63m0_power(lcd, FB_BLANK_POWERDOWN);
}