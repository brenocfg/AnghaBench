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
 scalar_t__ OK ; 
 scalar_t__ SKIP ; 
 scalar_t__ cur_test_outcome ; 

void
tinytest_set_test_skipped_(void)
{
	if (cur_test_outcome==OK)
		cur_test_outcome = SKIP;
}