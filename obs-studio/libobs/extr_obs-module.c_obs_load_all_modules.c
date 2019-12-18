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
 int /*<<< orphan*/  load_all_callback ; 
 int /*<<< orphan*/  obs_find_modules (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  obs_load_all_modules_name ; 
 int /*<<< orphan*/  profile_end (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  profile_start (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  reset_win32_symbol_paths () ; 
 int /*<<< orphan*/  reset_win32_symbol_paths_name ; 

void obs_load_all_modules(void)
{
	profile_start(obs_load_all_modules_name);
	obs_find_modules(load_all_callback, NULL);
#ifdef _WIN32
	profile_start(reset_win32_symbol_paths_name);
	reset_win32_symbol_paths();
	profile_end(reset_win32_symbol_paths_name);
#endif
	profile_end(obs_load_all_modules_name);
}