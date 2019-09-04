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
struct hdspm {int control_register; } ;

/* Variables and functions */
 int HDSPM_DoubleSpeed ; 
 int HDSPM_QuadSpeed ; 

__attribute__((used)) static int hdspm_rate_multiplier(struct hdspm *hdspm, int rate)
{
	if (rate <= 48000) {
		if (hdspm->control_register & HDSPM_QuadSpeed)
			return rate * 4;
		else if (hdspm->control_register &
				HDSPM_DoubleSpeed)
			return rate * 2;
	}
	return rate;
}