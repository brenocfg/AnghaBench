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
 int HSW_EXT_CSTATE_COUNT ; 
 int /*<<< orphan*/ * current_count ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  is_valid ; 
 int /*<<< orphan*/ * previous_count ; 

void hsw_ext_unregister(void)
{
	int num;
	free(is_valid);
	for (num = 0; num < HSW_EXT_CSTATE_COUNT; num++) {
		free(previous_count[num]);
		free(current_count[num]);
	}
}