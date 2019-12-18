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
 int /*<<< orphan*/  Assert (int) ; 
 int BLCKSZ ; 
 int FSM_CAT_STEP ; 
 int MaxFSMRequestSize ; 

__attribute__((used)) static uint8
fsm_space_avail_to_cat(Size avail)
{
	int			cat;

	Assert(avail < BLCKSZ);

	if (avail >= MaxFSMRequestSize)
		return 255;

	cat = avail / FSM_CAT_STEP;

	/*
	 * The highest category, 255, is reserved for MaxFSMRequestSize bytes or
	 * more.
	 */
	if (cat > 254)
		cat = 254;

	return (uint8) cat;
}