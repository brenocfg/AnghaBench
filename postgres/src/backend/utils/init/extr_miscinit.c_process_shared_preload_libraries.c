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
 int /*<<< orphan*/  load_libraries (int /*<<< orphan*/ ,char*,int) ; 
 int process_shared_preload_libraries_in_progress ; 
 int /*<<< orphan*/  shared_preload_libraries_string ; 

void
process_shared_preload_libraries(void)
{
	process_shared_preload_libraries_in_progress = true;
	load_libraries(shared_preload_libraries_string,
				   "shared_preload_libraries",
				   false);
	process_shared_preload_libraries_in_progress = false;
}