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
struct oxygen {int dummy; } ;

/* Variables and functions */
 unsigned int OXYGEN_PLAY_DAC0_SOURCE_MASK ; 
 unsigned int OXYGEN_PLAY_DAC1_SOURCE_MASK ; 

__attribute__((used)) static unsigned int se6x_adjust_dac_routing(struct oxygen *chip,
					    unsigned int play_routing)
{
	/* route the same stereo pair to DAC0 and DAC1 */
	return ( play_routing       & OXYGEN_PLAY_DAC0_SOURCE_MASK) |
	       ((play_routing << 2) & OXYGEN_PLAY_DAC1_SOURCE_MASK);
}