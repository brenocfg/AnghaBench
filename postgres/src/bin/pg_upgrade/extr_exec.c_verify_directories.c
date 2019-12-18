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
 int R_OK ; 
 int W_OK ; 
 int X_OK ; 
 scalar_t__ access (char*,int) ; 
 int /*<<< orphan*/  check_bin_dir (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  check_data_dir (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  new_cluster ; 
 int /*<<< orphan*/  old_cluster ; 
 int /*<<< orphan*/  pg_fatal (char*) ; 
 scalar_t__ win32_check_directory_write_permissions () ; 

void
verify_directories(void)
{
#ifndef WIN32
	if (access(".", R_OK | W_OK | X_OK) != 0)
#else
	if (win32_check_directory_write_permissions() != 0)
#endif
		pg_fatal("You must have read and write access in the current directory.\n");

	check_bin_dir(&old_cluster);
	check_data_dir(&old_cluster);
	check_bin_dir(&new_cluster);
	check_data_dir(&new_cluster);
}