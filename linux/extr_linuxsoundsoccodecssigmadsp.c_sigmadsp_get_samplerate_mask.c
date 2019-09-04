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
struct TYPE_2__ {scalar_t__ count; } ;
struct sigmadsp {TYPE_1__ rate_constraints; } ;

/* Variables and functions */
 unsigned int BIT (int) ; 
 int sigmadsp_rate_to_index (struct sigmadsp*,unsigned int) ; 

__attribute__((used)) static unsigned int sigmadsp_get_samplerate_mask(struct sigmadsp *sigmadsp,
	unsigned int samplerate)
{
	int samplerate_index;

	if (samplerate == 0)
		return 0;

	if (sigmadsp->rate_constraints.count) {
		samplerate_index = sigmadsp_rate_to_index(sigmadsp, samplerate);
		if (samplerate_index < 0)
			return 0;

		return BIT(samplerate_index);
	} else {
		return ~0;
	}
}