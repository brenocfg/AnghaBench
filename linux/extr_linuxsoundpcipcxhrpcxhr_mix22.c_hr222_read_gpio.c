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
struct pcxhr_mgr {int dsp_reset; } ;

/* Variables and functions */
 int PCXHR_DSP_RESET_GPO_MASK ; 
 int PCXHR_DSP_RESET_GPO_OFFSET ; 
 unsigned char PCXHR_INPB (struct pcxhr_mgr*,int /*<<< orphan*/ ) ; 
 unsigned char PCXHR_STAT_GPI_MASK ; 
 int PCXHR_STAT_GPI_OFFSET ; 
 int /*<<< orphan*/  PCXHR_XLX_STATUS ; 

int hr222_read_gpio(struct pcxhr_mgr *mgr, int is_gpi, int *value)
{
	if (is_gpi) {
		unsigned char reg = PCXHR_INPB(mgr, PCXHR_XLX_STATUS);
		*value = (int)(reg & PCXHR_STAT_GPI_MASK) >>
			      PCXHR_STAT_GPI_OFFSET;
	} else {
		*value = (int)(mgr->dsp_reset & PCXHR_DSP_RESET_GPO_MASK) >>
			 PCXHR_DSP_RESET_GPO_OFFSET;
	}
	return 0;
}