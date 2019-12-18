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
struct hdsp {int control_register; scalar_t__ system_sample_rate; } ;

/* Variables and functions */
 int HDSP_ClockModeMaster ; 
 scalar_t__ hdsp_external_sample_rate (struct hdsp*) ; 

__attribute__((used)) static int hdsp_system_clock_mode(struct hdsp *hdsp)
{
	if (hdsp->control_register & HDSP_ClockModeMaster)
		return 0;
	else if (hdsp_external_sample_rate(hdsp) != hdsp->system_sample_rate)
			return 0;
	return 1;
}