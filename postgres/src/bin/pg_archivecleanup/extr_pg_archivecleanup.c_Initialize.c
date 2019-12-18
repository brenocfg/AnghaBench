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
struct stat {int /*<<< orphan*/  st_mode; } ;

/* Variables and functions */
 int /*<<< orphan*/  S_ISDIR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  archiveLocation ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  pg_log_error (char*,int /*<<< orphan*/ ) ; 
 scalar_t__ stat (int /*<<< orphan*/ ,struct stat*) ; 

__attribute__((used)) static void
Initialize(void)
{
	/*
	 * This code assumes that archiveLocation is a directory, so we use stat
	 * to test if it's accessible.
	 */
	struct stat stat_buf;

	if (stat(archiveLocation, &stat_buf) != 0 ||
		!S_ISDIR(stat_buf.st_mode))
	{
		pg_log_error("archive location \"%s\" does not exist",
					 archiveLocation);
		exit(2);
	}
}