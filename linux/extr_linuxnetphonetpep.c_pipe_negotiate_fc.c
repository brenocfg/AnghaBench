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
typedef  scalar_t__ u8 ;

/* Variables and functions */
 scalar_t__ PN_MAX_FLOW_CONTROL ; 
 scalar_t__ PN_NO_FLOW_CONTROL ; 

__attribute__((used)) static u8 pipe_negotiate_fc(const u8 *fcs, unsigned int n)
{
	unsigned int i;
	u8 final_fc = PN_NO_FLOW_CONTROL;

	for (i = 0; i < n; i++) {
		u8 fc = fcs[i];

		if (fc > final_fc && fc < PN_MAX_FLOW_CONTROL)
			final_fc = fc;
	}
	return final_fc;
}