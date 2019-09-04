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
struct device {int dummy; } ;
struct ad7152_chip_info {size_t filter_rate_setup; } ;

/* Variables and functions */
 int** ad7152_filter_rate_table ; 
 int /*<<< orphan*/  dev_to_iio_dev (struct device*) ; 
 struct ad7152_chip_info* iio_priv (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ad7152_read_raw_samp_freq(struct device *dev, int *val)
{
	struct ad7152_chip_info *chip = iio_priv(dev_to_iio_dev(dev));

	*val = ad7152_filter_rate_table[chip->filter_rate_setup][0];

	return 0;
}