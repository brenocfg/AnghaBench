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
struct nvidia_par {int paneltweak; int Chipset; } ;
struct _riva_hw_state {int bpp; } ;

/* Variables and functions */

__attribute__((used)) static int nvidia_panel_tweak(struct nvidia_par *par,
			      struct _riva_hw_state *state)
{
	int tweak = 0;

   if (par->paneltweak) {
	   tweak = par->paneltweak;
   } else {
	   /* begin flat panel hacks */
	   /* This is unfortunate, but some chips need this register
	      tweaked or else you get artifacts where adjacent pixels are
	      swapped.  There are no hard rules for what to set here so all
	      we can do is experiment and apply hacks. */

	   if(((par->Chipset & 0xffff) == 0x0328) && (state->bpp == 32)) {
		   /* At least one NV34 laptop needs this workaround. */
		   tweak = -1;
	   }

	   if((par->Chipset & 0xfff0) == 0x0310) {
		   tweak = 1;
	   }
	   /* end flat panel hacks */
   }

   return tweak;
}