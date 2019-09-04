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
struct iio_channel {int dummy; } ;

/* Variables and functions */
 int iio_read_channel_processed (struct iio_channel*,int*) ; 

__attribute__((used)) static inline int ac_available(struct iio_channel *channel_vac)
{
	int val, err;

	if (!channel_vac)
		return 0;

	err = iio_read_channel_processed(channel_vac, &val);
	if (err < 0)
		return 0;
	return val > 4500;
}