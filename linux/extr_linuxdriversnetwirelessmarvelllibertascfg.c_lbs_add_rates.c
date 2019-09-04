#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
struct TYPE_3__ {int bitrate; } ;

/* Variables and functions */
 int ARRAY_SIZE (TYPE_1__*) ; 
 TYPE_1__* lbs_rates ; 

__attribute__((used)) static int lbs_add_rates(u8 *rates)
{
	size_t i;

	for (i = 0; i < ARRAY_SIZE(lbs_rates); i++) {
		u8 rate = lbs_rates[i].bitrate / 5;
		if (rate == 0x02 || rate == 0x04 ||
		    rate == 0x0b || rate == 0x16)
			rate |= 0x80;
		rates[i] = rate;
	}
	return ARRAY_SIZE(lbs_rates);
}