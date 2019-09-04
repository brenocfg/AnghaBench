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
struct ad_sigma_delta {int dummy; } ;
struct ad7780_state {int gain; struct ad7780_chip_info* chip_info; } ;
struct ad7780_chip_info {unsigned int pattern_mask; unsigned int pattern; } ;

/* Variables and functions */
 unsigned int AD7780_ERR ; 
 unsigned int AD7780_GAIN ; 
 int EIO ; 
 struct ad7780_state* ad_sigma_delta_to_ad7780 (struct ad_sigma_delta*) ; 

__attribute__((used)) static int ad7780_postprocess_sample(struct ad_sigma_delta *sigma_delta,
				     unsigned int raw_sample)
{
	struct ad7780_state *st = ad_sigma_delta_to_ad7780(sigma_delta);
	const struct ad7780_chip_info *chip_info = st->chip_info;

	if ((raw_sample & AD7780_ERR) ||
	    ((raw_sample & chip_info->pattern_mask) != chip_info->pattern))
		return -EIO;

	if (raw_sample & AD7780_GAIN)
		st->gain = 1;
	else
		st->gain = 128;

	return 0;
}