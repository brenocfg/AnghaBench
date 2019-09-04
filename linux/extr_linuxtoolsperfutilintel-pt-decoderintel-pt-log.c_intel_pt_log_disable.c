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
 scalar_t__ f ; 
 int /*<<< orphan*/  fflush (scalar_t__) ; 
 int intel_pt_enable_logging ; 

void intel_pt_log_disable(void)
{
	if (f)
		fflush(f);
	intel_pt_enable_logging = false;
}