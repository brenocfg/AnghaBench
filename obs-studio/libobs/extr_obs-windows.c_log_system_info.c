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
struct win_version_info {int major; int minor; } ;

/* Variables and functions */
 int /*<<< orphan*/  get_win_ver (struct win_version_info*) ; 
 int /*<<< orphan*/  log_admin_status () ; 
 int /*<<< orphan*/  log_aero () ; 
 int /*<<< orphan*/  log_available_memory () ; 
 int /*<<< orphan*/  log_gaming_features () ; 
 int /*<<< orphan*/  log_processor_cores () ; 
 int /*<<< orphan*/  log_processor_info () ; 
 int /*<<< orphan*/  log_security_products () ; 
 int /*<<< orphan*/  log_windows_version () ; 
 int win_ver ; 

void log_system_info(void)
{
	struct win_version_info ver;
	get_win_ver(&ver);

	win_ver = (ver.major << 8) | ver.minor;

	log_processor_info();
	log_processor_cores();
	log_available_memory();
	log_windows_version();
	log_admin_status();
	log_aero();
	log_gaming_features();
	log_security_products();
}