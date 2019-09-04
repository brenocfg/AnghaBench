#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct spi_master {int dummy; } ;
struct meson_spicc_device {TYPE_1__* pdev; scalar_t__ base; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 scalar_t__ SPICC_CONREG ; 
 int /*<<< orphan*/  SPICC_ENABLE ; 
 scalar_t__ SPICC_INTREG ; 
 int /*<<< orphan*/  device_reset_optional (int /*<<< orphan*/ *) ; 
 struct meson_spicc_device* spi_master_get_devdata (struct spi_master*) ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  writel_bits_relaxed (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static int meson_spicc_unprepare_transfer(struct spi_master *master)
{
	struct meson_spicc_device *spicc = spi_master_get_devdata(master);

	/* Disable all IRQs */
	writel(0, spicc->base + SPICC_INTREG);

	/* Disable controller */
	writel_bits_relaxed(SPICC_ENABLE, 0, spicc->base + SPICC_CONREG);

	device_reset_optional(&spicc->pdev->dev);

	return 0;
}