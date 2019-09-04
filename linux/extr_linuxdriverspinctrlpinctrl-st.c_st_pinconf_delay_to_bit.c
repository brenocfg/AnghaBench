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
struct st_pctl_data {unsigned int* output_delays; int noutput_delays; unsigned int* input_delays; int ninput_delays; } ;

/* Variables and functions */
 scalar_t__ ST_PINCONF_UNPACK_OE (unsigned long) ; 
 unsigned int UINT_MAX ; 
 unsigned int abs (unsigned int) ; 
 int /*<<< orphan*/  pr_warn (char*,unsigned int,unsigned int const) ; 

__attribute__((used)) static unsigned long st_pinconf_delay_to_bit(unsigned int delay,
	const struct st_pctl_data *data, unsigned long config)
{
	const unsigned int *delay_times;
	int num_delay_times, i, closest_index = -1;
	unsigned int closest_divergence = UINT_MAX;

	if (ST_PINCONF_UNPACK_OE(config)) {
		delay_times = data->output_delays;
		num_delay_times = data->noutput_delays;
	} else {
		delay_times = data->input_delays;
		num_delay_times = data->ninput_delays;
	}

	for (i = 0; i < num_delay_times; i++) {
		unsigned int divergence = abs(delay - delay_times[i]);

		if (divergence == 0)
			return i;

		if (divergence < closest_divergence) {
			closest_divergence = divergence;
			closest_index = i;
		}
	}

	pr_warn("Attempt to set delay %d, closest available %d\n",
	     delay, delay_times[closest_index]);

	return closest_index;
}