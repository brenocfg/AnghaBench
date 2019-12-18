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
 int /*<<< orphan*/  ERRCODE_INVALID_PARAMETER_VALUE ; 
 int /*<<< orphan*/  ERROR ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errcode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errdetail (char*) ; 
 int /*<<< orphan*/  errmsg (char*,char const*) ; 
 int /*<<< orphan*/ * first_dir_separator (char const*) ; 
 int strlen (char const*) ; 
 scalar_t__ strstr (char const*,char*) ; 

__attribute__((used)) static void
check_valid_version_name(const char *versionname)
{
	int			namelen = strlen(versionname);

	/*
	 * Disallow empty names (we could possibly allow this, but there seems
	 * little point).
	 */
	if (namelen == 0)
		ereport(ERROR,
				(errcode(ERRCODE_INVALID_PARAMETER_VALUE),
				 errmsg("invalid extension version name: \"%s\"", versionname),
				 errdetail("Version names must not be empty.")));

	/*
	 * No double dashes, since that would make script filenames ambiguous.
	 */
	if (strstr(versionname, "--"))
		ereport(ERROR,
				(errcode(ERRCODE_INVALID_PARAMETER_VALUE),
				 errmsg("invalid extension version name: \"%s\"", versionname),
				 errdetail("Version names must not contain \"--\".")));

	/*
	 * No leading or trailing dash either.
	 */
	if (versionname[0] == '-' || versionname[namelen - 1] == '-')
		ereport(ERROR,
				(errcode(ERRCODE_INVALID_PARAMETER_VALUE),
				 errmsg("invalid extension version name: \"%s\"", versionname),
				 errdetail("Version names must not begin or end with \"-\".")));

	/*
	 * No directory separators either (this is sufficient to prevent ".."
	 * style attacks).
	 */
	if (first_dir_separator(versionname) != NULL)
		ereport(ERROR,
				(errcode(ERRCODE_INVALID_PARAMETER_VALUE),
				 errmsg("invalid extension version name: \"%s\"", versionname),
				 errdetail("Version names must not contain directory separator characters.")));
}