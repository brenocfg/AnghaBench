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
 int /*<<< orphan*/  ath79_spi_cleanup_cs (struct spi_device*) ; 
 int /*<<< orphan*/  spi_bitbang_cleanup (struct spi_device*) ; 

__attribute__((used)) static void ath79_spi_cleanup(struct spi_device *spi)
{
	ath79_spi_cleanup_cs(spi);
	spi_bitbang_cleanup(spi);
}