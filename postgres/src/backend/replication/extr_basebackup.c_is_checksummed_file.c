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
 char** noChecksumFiles ; 
 scalar_t__ strcmp (char const* const,char const*) ; 
 scalar_t__ strncmp (char const*,char*,int) ; 

__attribute__((used)) static bool
is_checksummed_file(const char *fullpath, const char *filename)
{
	const char *const *f;

	/* Check that the file is in a tablespace */
	if (strncmp(fullpath, "./global/", 9) == 0 ||
		strncmp(fullpath, "./base/", 7) == 0 ||
		strncmp(fullpath, "/", 1) == 0)
	{
		/* Compare file against noChecksumFiles skiplist */
		for (f = noChecksumFiles; *f; f++)
			if (strcmp(*f, filename) == 0)
				return false;

		return true;
	}
	else
		return false;
}