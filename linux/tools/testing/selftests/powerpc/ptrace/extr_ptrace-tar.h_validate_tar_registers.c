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
 int TEST_FAIL ; 
 int TEST_PASS ; 

int validate_tar_registers(unsigned long *reg, unsigned long tar,
				unsigned long ppr, unsigned long dscr)
{
	int match = 1;

	if (reg[0] != tar)
		match = 0;

	if (reg[1] != ppr)
		match = 0;

	if (reg[2] != dscr)
		match = 0;

	if (!match)
		return TEST_FAIL;
	return TEST_PASS;
}