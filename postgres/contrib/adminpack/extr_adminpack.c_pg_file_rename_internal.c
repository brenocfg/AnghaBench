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
typedef  int /*<<< orphan*/  text ;

/* Variables and functions */
 scalar_t__ ENOENT ; 
 int /*<<< orphan*/  ERRCODE_DUPLICATE_FILE ; 
 int /*<<< orphan*/  ERRCODE_UNDEFINED_FILE ; 
 int /*<<< orphan*/  ERROR ; 
 int /*<<< orphan*/  WARNING ; 
 int /*<<< orphan*/  W_OK ; 
 int access (char*,int /*<<< orphan*/ ) ; 
 char* convert_and_check_filename (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errcode_for_file_access () ; 
 int /*<<< orphan*/  errmsg (char*,char*,...) ; 
 scalar_t__ errno ; 
 scalar_t__ rename (char*,char*) ; 

__attribute__((used)) static bool
pg_file_rename_internal(text *file1, text *file2, text *file3)
{
	char	   *fn1,
			   *fn2,
			   *fn3;
	int			rc;

	fn1 = convert_and_check_filename(file1, false);
	fn2 = convert_and_check_filename(file2, false);

	if (file3 == NULL)
		fn3 = NULL;
	else
		fn3 = convert_and_check_filename(file3, false);

	if (access(fn1, W_OK) < 0)
	{
		ereport(WARNING,
				(errcode_for_file_access(),
				 errmsg("file \"%s\" is not accessible: %m", fn1)));

		return false;
	}

	if (fn3 && access(fn2, W_OK) < 0)
	{
		ereport(WARNING,
				(errcode_for_file_access(),
				 errmsg("file \"%s\" is not accessible: %m", fn2)));

		return false;
	}

	rc = access(fn3 ? fn3 : fn2, W_OK);
	if (rc >= 0 || errno != ENOENT)
	{
		ereport(ERROR,
				(ERRCODE_DUPLICATE_FILE,
				 errmsg("cannot rename to target file \"%s\"",
						fn3 ? fn3 : fn2)));
	}

	if (fn3)
	{
		if (rename(fn2, fn3) != 0)
		{
			ereport(ERROR,
					(errcode_for_file_access(),
					 errmsg("could not rename \"%s\" to \"%s\": %m",
							fn2, fn3)));
		}
		if (rename(fn1, fn2) != 0)
		{
			ereport(WARNING,
					(errcode_for_file_access(),
					 errmsg("could not rename \"%s\" to \"%s\": %m",
							fn1, fn2)));

			if (rename(fn3, fn2) != 0)
			{
				ereport(ERROR,
						(errcode_for_file_access(),
						 errmsg("could not rename \"%s\" back to \"%s\": %m",
								fn3, fn2)));
			}
			else
			{
				ereport(ERROR,
						(ERRCODE_UNDEFINED_FILE,
						 errmsg("renaming \"%s\" to \"%s\" was reverted",
								fn2, fn3)));
			}
		}
	}
	else if (rename(fn1, fn2) != 0)
	{
		ereport(ERROR,
				(errcode_for_file_access(),
				 errmsg("could not rename \"%s\" to \"%s\": %m", fn1, fn2)));
	}

	return true;
}