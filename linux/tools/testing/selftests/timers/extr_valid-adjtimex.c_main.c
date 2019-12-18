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
 int ksft_exit_fail () ; 
 int ksft_exit_pass () ; 
 scalar_t__ validate_freq () ; 
 scalar_t__ validate_set_offset () ; 

int main(int argc, char **argv)
{
	if (validate_freq())
		return ksft_exit_fail();

	if (validate_set_offset())
		return ksft_exit_fail();

	return ksft_exit_pass();
}