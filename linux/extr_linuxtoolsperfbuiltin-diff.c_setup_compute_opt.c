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
 scalar_t__ COMPUTE_WEIGHTED_DIFF ; 
 int EINVAL ; 
 scalar_t__ compute ; 
 int /*<<< orphan*/  pr_err (char*,char*) ; 
 int setup_compute_opt_wdiff (char*) ; 

__attribute__((used)) static int setup_compute_opt(char *opt)
{
	if (compute == COMPUTE_WEIGHTED_DIFF)
		return setup_compute_opt_wdiff(opt);

	if (opt) {
		pr_err("Failed: extra option specified '%s'", opt);
		return -EINVAL;
	}

	return 0;
}