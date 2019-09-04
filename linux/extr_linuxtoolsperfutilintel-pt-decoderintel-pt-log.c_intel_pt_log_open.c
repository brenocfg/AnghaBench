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
 scalar_t__ fopen (int /*<<< orphan*/ *,char*) ; 
 int intel_pt_enable_logging ; 
 int /*<<< orphan*/ * log_name ; 

__attribute__((used)) static int intel_pt_log_open(void)
{
	if (!intel_pt_enable_logging)
		return -1;

	if (f)
		return 0;

	if (!log_name[0])
		return -1;

	f = fopen(log_name, "w+");
	if (!f) {
		intel_pt_enable_logging = false;
		return -1;
	}

	return 0;
}