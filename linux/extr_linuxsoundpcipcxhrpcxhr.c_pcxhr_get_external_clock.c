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
struct pcxhr_mgr {scalar_t__ is_hr_stereo; } ;
typedef  enum pcxhr_clock_type { ____Placeholder_pcxhr_clock_type } pcxhr_clock_type ;

/* Variables and functions */
 int hr222_get_external_clock (struct pcxhr_mgr*,int,int*) ; 
 int pcxhr_sub_get_external_clock (struct pcxhr_mgr*,int,int*) ; 

int pcxhr_get_external_clock(struct pcxhr_mgr *mgr,
			     enum pcxhr_clock_type clock_type,
			     int *sample_rate)
{
	if (mgr->is_hr_stereo)
		return hr222_get_external_clock(mgr, clock_type,
						sample_rate);
	else
		return pcxhr_sub_get_external_clock(mgr, clock_type,
						    sample_rate);
}