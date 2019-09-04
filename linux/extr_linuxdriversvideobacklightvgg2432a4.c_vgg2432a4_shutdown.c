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
 int /*<<< orphan*/  ili9320_shutdown (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spi_get_drvdata (struct spi_device*) ; 

__attribute__((used)) static void vgg2432a4_shutdown(struct spi_device *spi)
{
	ili9320_shutdown(spi_get_drvdata(spi));
}