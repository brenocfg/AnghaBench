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
typedef  int /*<<< orphan*/  __m128 ;

/* Variables and functions */
 int /*<<< orphan*/  _mm_load_ps (float const*) ; 
 int /*<<< orphan*/  _mm_max_ps (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  abs_ps (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hmax_ps (float,int /*<<< orphan*/ ) ; 

__attribute__((used)) static float get_sample_peak(__m128 previous_samples, const float *samples,
			     size_t nr_samples)
{
	__m128 peak = previous_samples;
	for (size_t i = 0; (i + 3) < nr_samples; i += 4) {
		__m128 new_work = _mm_load_ps(&samples[i]);
		peak = _mm_max_ps(peak, abs_ps(new_work));
	}

	float r;
	hmax_ps(r, peak);
	return r;
}