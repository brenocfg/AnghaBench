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
typedef  int /*<<< orphan*/  u32 ;
struct dln2_spi {TYPE_1__* pdev; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DLN2_SPI_GET_MAX_FREQUENCY ; 
 int /*<<< orphan*/  DLN2_SPI_GET_MIN_FREQUENCY ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int dln2_spi_get_speed (struct dln2_spi*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int dln2_spi_get_speed_range(struct dln2_spi *dln2, u32 *fmin, u32 *fmax)
{
	int ret;

	ret = dln2_spi_get_speed(dln2, DLN2_SPI_GET_MIN_FREQUENCY, fmin);
	if (ret < 0)
		return ret;

	ret = dln2_spi_get_speed(dln2, DLN2_SPI_GET_MAX_FREQUENCY, fmax);
	if (ret < 0)
		return ret;

	dev_dbg(&dln2->pdev->dev, "freq_min = %d, freq_max = %d\n",
		*fmin, *fmax);

	return 0;
}