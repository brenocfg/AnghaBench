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
struct spi_device {scalar_t__ irq; } ;
struct iio_dev {int dummy; } ;
struct ad7280_state {int ctrl_hb; int /*<<< orphan*/  iio_attr; int /*<<< orphan*/  channels; } ;

/* Variables and functions */
 int /*<<< orphan*/  AD7280A_CONTROL_HB ; 
 int AD7280A_CTRL_HB_PWRDN_SW ; 
 int /*<<< orphan*/  AD7280A_DEVADDR_MASTER ; 
 int /*<<< orphan*/  ad7280_write (struct ad7280_state*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  free_irq (scalar_t__,struct iio_dev*) ; 
 int /*<<< orphan*/  iio_device_unregister (struct iio_dev*) ; 
 struct ad7280_state* iio_priv (struct iio_dev*) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 
 struct iio_dev* spi_get_drvdata (struct spi_device*) ; 

__attribute__((used)) static int ad7280_remove(struct spi_device *spi)
{
	struct iio_dev *indio_dev = spi_get_drvdata(spi);
	struct ad7280_state *st = iio_priv(indio_dev);

	if (spi->irq > 0)
		free_irq(spi->irq, indio_dev);
	iio_device_unregister(indio_dev);

	ad7280_write(st, AD7280A_DEVADDR_MASTER, AD7280A_CONTROL_HB, 1,
		     AD7280A_CTRL_HB_PWRDN_SW | st->ctrl_hb);

	kfree(st->channels);
	kfree(st->iio_attr);

	return 0;
}