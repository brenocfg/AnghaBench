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
struct pcxhr_mgr {unsigned char dsp_reset; } ;

/* Variables and functions */
 int /*<<< orphan*/  PCXHR_DSP_RESET ; 
 unsigned char PCXHR_DSP_RESET_GPO_MASK ; 
 int PCXHR_DSP_RESET_GPO_OFFSET ; 
 int /*<<< orphan*/  PCXHR_OUTPB (struct pcxhr_mgr*,int /*<<< orphan*/ ,unsigned char) ; 

int hr222_write_gpo(struct pcxhr_mgr *mgr, int value)
{
	unsigned char reg = mgr->dsp_reset & ~PCXHR_DSP_RESET_GPO_MASK;

	reg |= (unsigned char)(value << PCXHR_DSP_RESET_GPO_OFFSET) &
	       PCXHR_DSP_RESET_GPO_MASK;

	PCXHR_OUTPB(mgr, PCXHR_DSP_RESET, reg);
	mgr->dsp_reset = reg;
	return 0;
}