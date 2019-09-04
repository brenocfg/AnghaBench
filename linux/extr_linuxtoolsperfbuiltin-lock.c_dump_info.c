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
 int /*<<< orphan*/  dump_map () ; 
 int /*<<< orphan*/  dump_threads () ; 
 scalar_t__ info_map ; 
 scalar_t__ info_threads ; 
 int /*<<< orphan*/  pr_err (char*) ; 

__attribute__((used)) static int dump_info(void)
{
	int rc = 0;

	if (info_threads)
		dump_threads();
	else if (info_map)
		dump_map();
	else {
		rc = -1;
		pr_err("Unknown type of information\n");
	}

	return rc;
}