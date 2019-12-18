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
 scalar_t__ SF_IS_DRUM_BANK (int) ; 
 int SF_MAX_INSTRUMENTS ; 
 int SF_MAX_PRESETS ; 

__attribute__((used)) static int
get_index(int bank, int instr, int key)
{
	int index;
	if (SF_IS_DRUM_BANK(bank))
		index = key + SF_MAX_INSTRUMENTS;
	else
		index = instr;
	index = index % SF_MAX_PRESETS;
	if (index < 0)
		return -1;
	return index;
}