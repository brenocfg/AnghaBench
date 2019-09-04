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
struct sample {int dummy; } ;

/* Variables and functions */
 scalar_t__ MAX_FREQ_ERROR ; 
 double MAX_STDDEV ; 
 int MEAN_SAMPLE_INTERVAL ; 
 int SAMPLES ; 
 int STEP_INTERVAL ; 
 scalar_t__ fabs (double) ; 
 int /*<<< orphan*/  get_sample (struct sample*) ; 
 int mono_freq_offset ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int rand () ; 
 int /*<<< orphan*/  regress (struct sample*,int,double*,double*,double*,double*) ; 
 int /*<<< orphan*/  reset_ntp_error () ; 
 int /*<<< orphan*/  set_frequency (double) ; 
 int /*<<< orphan*/  usleep (int) ; 

__attribute__((used)) static int run_test(int calibration, double freq_base, double freq_step)
{
	struct sample samples[SAMPLES];
	double intercept, slope, stddev1, max1, stddev2, max2;
	double freq_error1, freq_error2;
	int i;

	set_frequency(freq_base);

	for (i = 0; i < 10; i++)
		usleep(1e6 * MEAN_SAMPLE_INTERVAL / 10);

	reset_ntp_error();

	set_frequency(freq_base + freq_step);

	for (i = 0; i < 10; i++)
		usleep(rand() % 2000000 * STEP_INTERVAL / 10);

	set_frequency(freq_base);

	for (i = 0; i < SAMPLES; i++) {
		usleep(rand() % 2000000 * MEAN_SAMPLE_INTERVAL);
		get_sample(&samples[i]);
	}

	if (calibration) {
		regress(samples, SAMPLES, &intercept, &slope, &stddev1, &max1);
		mono_freq_offset = slope;
		printf("CLOCK_MONOTONIC_RAW frequency offset: %11.3f ppm\n",
		       1e6 * mono_freq_offset);
		return 0;
	}

	regress(samples, SAMPLES / 2, &intercept, &slope, &stddev1, &max1);
	freq_error1 = slope * (1.0 - mono_freq_offset) - mono_freq_offset -
			freq_base;

	regress(samples + SAMPLES / 2, SAMPLES / 2, &intercept, &slope,
		&stddev2, &max2);
	freq_error2 = slope * (1.0 - mono_freq_offset) - mono_freq_offset -
			freq_base;

	printf("%6.0f %+10.3f %6.0f %7.0f %+10.3f %6.0f %7.0f\t",
	       1e6 * freq_step,
	       1e6 * freq_error1, 1e9 * stddev1, 1e9 * max1,
	       1e6 * freq_error2, 1e9 * stddev2, 1e9 * max2);

	if (fabs(freq_error2) > MAX_FREQ_ERROR || stddev2 > MAX_STDDEV) {
		printf("[FAIL]\n");
		return 1;
	}

	printf("[OK]\n");
	return 0;
}