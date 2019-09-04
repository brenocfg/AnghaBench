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

/* Variables and functions */
 int /*<<< orphan*/  spi_set_drvdata (struct spi_device*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int ds1302_remove(struct spi_device *spi)
{
	spi_set_drvdata(spi, NULL);
	return 0;
}