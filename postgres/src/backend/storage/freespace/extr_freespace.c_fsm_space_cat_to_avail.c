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
typedef  int uint8 ;
typedef  int Size ;

/* Variables and functions */
 int FSM_CAT_STEP ; 
 int MaxFSMRequestSize ; 

__attribute__((used)) static Size
fsm_space_cat_to_avail(uint8 cat)
{
	/* The highest category represents exactly MaxFSMRequestSize bytes. */
	if (cat == 255)
		return MaxFSMRequestSize;
	else
		return cat * FSM_CAT_STEP;
}