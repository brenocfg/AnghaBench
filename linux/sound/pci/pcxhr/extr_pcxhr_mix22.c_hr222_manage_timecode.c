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
struct pcxhr_mgr {int /*<<< orphan*/  dsp_reset; } ;

/* Variables and functions */
 int /*<<< orphan*/  PCXHR_DSP_RESET ; 
 int /*<<< orphan*/  PCXHR_DSP_RESET_SMPTE ; 
 int /*<<< orphan*/  PCXHR_OUTPB (struct pcxhr_mgr*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int hr222_manage_timecode(struct pcxhr_mgr *mgr, int enable)
{
	if (enable)
		mgr->dsp_reset |= PCXHR_DSP_RESET_SMPTE;
	else
		mgr->dsp_reset &= ~PCXHR_DSP_RESET_SMPTE;

	PCXHR_OUTPB(mgr, PCXHR_DSP_RESET, mgr->dsp_reset);
	return 0;
}