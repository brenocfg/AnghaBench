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
 int /*<<< orphan*/  log_available_memory () ; 
 int /*<<< orphan*/  log_kernel_version () ; 
 int /*<<< orphan*/  log_os () ; 
 int /*<<< orphan*/  log_processor_cores () ; 
 int /*<<< orphan*/  log_processor_name () ; 
 int /*<<< orphan*/  log_processor_speed () ; 

void log_system_info(void)
{
	log_processor_name();
	log_processor_speed();
	log_processor_cores();
	log_available_memory();
	log_os();
	log_kernel_version();
}