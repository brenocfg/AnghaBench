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
 int /*<<< orphan*/  log_distribution_info () ; 
 int /*<<< orphan*/  log_kernel_version () ; 
 int /*<<< orphan*/  log_memory_info () ; 
 int /*<<< orphan*/  log_processor_cores () ; 
 int /*<<< orphan*/  log_processor_info () ; 
 int /*<<< orphan*/  log_x_info () ; 

void log_system_info(void)
{
#if defined(__linux__) || defined(__FreeBSD__)
	log_processor_info();
#endif
	log_processor_cores();
	log_memory_info();
	log_kernel_version();
#if defined(__linux__)
	log_distribution_info();
#endif
	log_x_info();
}