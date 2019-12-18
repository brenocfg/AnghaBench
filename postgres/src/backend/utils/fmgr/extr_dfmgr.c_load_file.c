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
 int /*<<< orphan*/  check_restricted_library_name (char const*) ; 
 char* expand_dynamic_library_name (char const*) ; 
 int /*<<< orphan*/  internal_load_library (char*) ; 
 int /*<<< orphan*/  internal_unload_library (char*) ; 
 int /*<<< orphan*/  pfree (char*) ; 

void
load_file(const char *filename, bool restricted)
{
	char	   *fullname;

	/* Apply security restriction if requested */
	if (restricted)
		check_restricted_library_name(filename);

	/* Expand the possibly-abbreviated filename to an exact path name */
	fullname = expand_dynamic_library_name(filename);

	/* Unload the library if currently loaded */
	internal_unload_library(fullname);

	/* Load the shared library */
	(void) internal_load_library(fullname);

	pfree(fullname);
}