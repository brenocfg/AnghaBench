#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct stat {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  handle; struct TYPE_4__* next; int /*<<< orphan*/  filename; } ;
typedef  int /*<<< orphan*/  (* PG_fini_t ) () ;
typedef  TYPE_1__ DynamicFileList ;

/* Variables and functions */
 int /*<<< orphan*/  ERROR ; 
 scalar_t__ SAME_INODE (struct stat,TYPE_1__) ; 
 int /*<<< orphan*/  clear_external_function_hash (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dlclose (int /*<<< orphan*/ ) ; 
 scalar_t__ dlsym (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errcode_for_file_access () ; 
 int /*<<< orphan*/  errmsg (char*,char const*) ; 
 TYPE_1__* file_list ; 
 int /*<<< orphan*/  free (char*) ; 
 int stat (char const*,struct stat*) ; 
 scalar_t__ strcmp (char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 () ; 

__attribute__((used)) static void
internal_unload_library(const char *libname)
{
#ifdef NOT_USED
	DynamicFileList *file_scanner,
			   *prv,
			   *nxt;
	struct stat stat_buf;
	PG_fini_t	PG_fini;

	/*
	 * We need to do stat() in order to determine whether this is the same
	 * file as a previously loaded file; it's also handy so as to give a good
	 * error message if bogus file name given.
	 */
	if (stat(libname, &stat_buf) == -1)
		ereport(ERROR,
				(errcode_for_file_access(),
				 errmsg("could not access file \"%s\": %m", libname)));

	/*
	 * We have to zap all entries in the list that match on either filename or
	 * inode, else internal_load_library() will still think it's present.
	 */
	prv = NULL;
	for (file_scanner = file_list; file_scanner != NULL; file_scanner = nxt)
	{
		nxt = file_scanner->next;
		if (strcmp(libname, file_scanner->filename) == 0 ||
			SAME_INODE(stat_buf, *file_scanner))
		{
			if (prv)
				prv->next = nxt;
			else
				file_list = nxt;

			/*
			 * If the library has a _PG_fini() function, call it.
			 */
			PG_fini = (PG_fini_t) dlsym(file_scanner->handle, "_PG_fini");
			if (PG_fini)
				(*PG_fini) ();

			clear_external_function_hash(file_scanner->handle);
			dlclose(file_scanner->handle);
			free((char *) file_scanner);
			/* prv does not change */
		}
		else
			prv = file_scanner;
	}
#endif							/* NOT_USED */
}