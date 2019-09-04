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
 int /*<<< orphan*/  init_oops_id () ; 
 scalar_t__ oops_id ; 
 int /*<<< orphan*/  pr_warn (char*,unsigned long long) ; 

void print_oops_end_marker(void)
{
	init_oops_id();
	pr_warn("---[ end trace %016llx ]---\n", (unsigned long long)oops_id);
}