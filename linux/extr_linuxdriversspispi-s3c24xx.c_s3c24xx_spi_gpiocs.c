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
struct s3c2410_spi_info {int /*<<< orphan*/  pin_cs; } ;

/* Variables and functions */
 int /*<<< orphan*/  gpio_set_value (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void s3c24xx_spi_gpiocs(struct s3c2410_spi_info *spi, int cs, int pol)
{
	gpio_set_value(spi->pin_cs, pol);
}