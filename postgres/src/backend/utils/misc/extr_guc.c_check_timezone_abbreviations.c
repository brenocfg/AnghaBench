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
typedef  scalar_t__ GucSource ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 scalar_t__ PGC_S_DEFAULT ; 
 void* load_tzoffsets (char*) ; 

__attribute__((used)) static bool
check_timezone_abbreviations(char **newval, void **extra, GucSource source)
{
	/*
	 * The boot_val given above for timezone_abbreviations is NULL. When we
	 * see this we just do nothing.  If this value isn't overridden from the
	 * config file then pg_timezone_abbrev_initialize() will eventually
	 * replace it with "Default".  This hack has two purposes: to avoid
	 * wasting cycles loading values that might soon be overridden from the
	 * config file, and to avoid trying to read the timezone abbrev files
	 * during InitializeGUCOptions().  The latter doesn't work in an
	 * EXEC_BACKEND subprocess because my_exec_path hasn't been set yet and so
	 * we can't locate PGSHAREDIR.
	 */
	if (*newval == NULL)
	{
		Assert(source == PGC_S_DEFAULT);
		return true;
	}

	/* OK, load the file and produce a malloc'd TimeZoneAbbrevTable */
	*extra = load_tzoffsets(*newval);

	/* tzparser.c returns NULL on failure, reporting via GUC_check_errmsg */
	if (!*extra)
		return false;

	return true;
}