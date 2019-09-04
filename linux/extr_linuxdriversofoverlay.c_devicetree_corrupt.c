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
 int DTSF_APPLY_FAIL ; 
 int DTSF_REVERT_FAIL ; 
 int devicetree_state_flags ; 

__attribute__((used)) static int devicetree_corrupt(void)
{
	return devicetree_state_flags &
		(DTSF_APPLY_FAIL | DTSF_REVERT_FAIL);
}