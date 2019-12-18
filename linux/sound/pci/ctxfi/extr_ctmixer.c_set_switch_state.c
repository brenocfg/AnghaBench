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
struct ct_mixer {int switch_state; } ;
typedef  enum CTALSA_MIXER_CTL { ____Placeholder_CTALSA_MIXER_CTL } CTALSA_MIXER_CTL ;

/* Variables and functions */
 int SWH_MIXER_START ; 

__attribute__((used)) static void
set_switch_state(struct ct_mixer *mixer,
		 enum CTALSA_MIXER_CTL type, unsigned char state)
{
	if (state)
		mixer->switch_state |= (0x1 << (type - SWH_MIXER_START));
	else
		mixer->switch_state &= ~(0x1 << (type - SWH_MIXER_START));
}