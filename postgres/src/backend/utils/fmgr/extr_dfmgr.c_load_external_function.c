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
typedef  int /*<<< orphan*/ * PGFunction ;

/* Variables and functions */
 int /*<<< orphan*/  ERRCODE_UNDEFINED_FUNCTION ; 
 int /*<<< orphan*/  ERROR ; 
 scalar_t__ dlsym (void*,char const*) ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errcode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errmsg (char*,char const*,char*) ; 
 char* expand_dynamic_library_name (char const*) ; 
 void* internal_load_library (char*) ; 
 int /*<<< orphan*/  pfree (char*) ; 

PGFunction
load_external_function(const char *filename, const char *funcname,
					   bool signalNotFound, void **filehandle)
{
	char	   *fullname;
	void	   *lib_handle;
	PGFunction	retval;

	/* Expand the possibly-abbreviated filename to an exact path name */
	fullname = expand_dynamic_library_name(filename);

	/* Load the shared library, unless we already did */
	lib_handle = internal_load_library(fullname);

	/* Return handle if caller wants it */
	if (filehandle)
		*filehandle = lib_handle;

	/* Look up the function within the library. */
	retval = (PGFunction) dlsym(lib_handle, funcname);

	if (retval == NULL && signalNotFound)
		ereport(ERROR,
				(errcode(ERRCODE_UNDEFINED_FUNCTION),
				 errmsg("could not find function \"%s\" in file \"%s\"",
						funcname, fullname)));

	pfree(fullname);
	return retval;
}