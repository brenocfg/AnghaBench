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

/* Variables and functions */
#define  CMDF_ROUND_DOWN 130 
 unsigned int CMDF_ROUND_MASK ; 
#define  CMDF_ROUND_NEAREST 129 
#define  CMDF_ROUND_UP 128 
 unsigned int DIV_ROUND_CLOSEST (unsigned int,unsigned int) ; 
 unsigned int DIV_ROUND_UP (unsigned int,unsigned int) ; 
 unsigned int DT2821_DIVIDER_MAX ; 
 unsigned int DT2821_OSC_BASE ; 
 unsigned int DT2821_PRESCALE (unsigned int) ; 
 unsigned int DT2821_PRESCALE_MAX ; 
 unsigned int DT2821_TMRCTR_DIVIDER (unsigned int) ; 
 unsigned int DT2821_TMRCTR_PRESCALE (unsigned int) ; 

__attribute__((used)) static unsigned int dt282x_ns_to_timer(unsigned int *ns, unsigned int flags)
{
	unsigned int prescale, base, divider;

	for (prescale = 0; prescale <= DT2821_PRESCALE_MAX; prescale++) {
		if (prescale == 1)	/* 0 and 1 are both divide by 1 */
			continue;
		base = DT2821_OSC_BASE * DT2821_PRESCALE(prescale);
		switch (flags & CMDF_ROUND_MASK) {
		case CMDF_ROUND_NEAREST:
		default:
			divider = DIV_ROUND_CLOSEST(*ns, base);
			break;
		case CMDF_ROUND_DOWN:
			divider = (*ns) / base;
			break;
		case CMDF_ROUND_UP:
			divider = DIV_ROUND_UP(*ns, base);
			break;
		}
		if (divider <= DT2821_DIVIDER_MAX)
			break;
	}
	if (divider > DT2821_DIVIDER_MAX) {
		prescale = DT2821_PRESCALE_MAX;
		divider = DT2821_DIVIDER_MAX;
		base = DT2821_OSC_BASE * DT2821_PRESCALE(prescale);
	}
	*ns = divider * base;
	return DT2821_TMRCTR_PRESCALE(prescale) |
	       DT2821_TMRCTR_DIVIDER(divider);
}