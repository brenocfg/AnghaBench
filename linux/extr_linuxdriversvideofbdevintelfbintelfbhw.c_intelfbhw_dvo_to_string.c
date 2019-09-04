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
 int DVOA_PORT ; 
 int DVOB_PORT ; 
 int DVOC_PORT ; 
 int LVDS_PORT ; 

const char * intelfbhw_dvo_to_string(int dvo)
{
	if (dvo & DVOA_PORT)
		return "DVO port A";
	else if (dvo & DVOB_PORT)
		return "DVO port B";
	else if (dvo & DVOC_PORT)
		return "DVO port C";
	else if (dvo & LVDS_PORT)
		return "LVDS port";
	else
		return NULL;
}