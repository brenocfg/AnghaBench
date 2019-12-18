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
struct config_generic {char* sourcefile; int sourceline; } ;

/* Variables and functions */
 int DEBUG3 ; 
 int /*<<< orphan*/  ERROR ; 
 scalar_t__ IsUnderPostmaster ; 
 int LOG ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*,char const*) ; 
 struct config_generic* find_option (char const*,int,int) ; 
 int /*<<< orphan*/  free (char*) ; 
 char* guc_strdup (int,char*) ; 

__attribute__((used)) static void
set_config_sourcefile(const char *name, char *sourcefile, int sourceline)
{
	struct config_generic *record;
	int			elevel;

	/*
	 * To avoid cluttering the log, only the postmaster bleats loudly about
	 * problems with the config file.
	 */
	elevel = IsUnderPostmaster ? DEBUG3 : LOG;

	record = find_option(name, true, elevel);
	/* should not happen */
	if (record == NULL)
		elog(ERROR, "unrecognized configuration parameter \"%s\"", name);

	sourcefile = guc_strdup(elevel, sourcefile);
	if (record->sourcefile)
		free(record->sourcefile);
	record->sourcefile = sourcefile;
	record->sourceline = sourceline;
}