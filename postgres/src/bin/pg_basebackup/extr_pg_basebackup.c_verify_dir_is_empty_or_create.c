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
 int /*<<< orphan*/  exit (int) ; 
 int pg_check_dir (char*) ; 
 int /*<<< orphan*/  pg_dir_create_mode ; 
 int /*<<< orphan*/  pg_log_error (char*,char*) ; 
 int pg_mkdir_p (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
verify_dir_is_empty_or_create(char *dirname, bool *created, bool *found)
{
	switch (pg_check_dir(dirname))
	{
		case 0:

			/*
			 * Does not exist, so create
			 */
			if (pg_mkdir_p(dirname, pg_dir_create_mode) == -1)
			{
				pg_log_error("could not create directory \"%s\": %m", dirname);
				exit(1);
			}
			if (created)
				*created = true;
			return;
		case 1:

			/*
			 * Exists, empty
			 */
			if (found)
				*found = true;
			return;
		case 2:
		case 3:
		case 4:

			/*
			 * Exists, not empty
			 */
			pg_log_error("directory \"%s\" exists but is not empty", dirname);
			exit(1);
		case -1:

			/*
			 * Access problem
			 */
			pg_log_error("could not access directory \"%s\": %m", dirname);
			exit(1);
	}
}