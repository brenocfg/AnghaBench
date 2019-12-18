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
 int /*<<< orphan*/  ERROR ; 
 int /*<<< orphan*/  free (char*) ; 
 char* guc_malloc (int /*<<< orphan*/ ,scalar_t__) ; 
 char* pgstat_stat_directory ; 
 char* pgstat_stat_filename ; 
 char* pgstat_stat_tmpname ; 
 int /*<<< orphan*/  sprintf (char*,char*,char const*) ; 
 scalar_t__ strlen (char const*) ; 

__attribute__((used)) static void
assign_pgstat_temp_directory(const char *newval, void *extra)
{
	/* check_canonical_path already canonicalized newval for us */
	char	   *dname;
	char	   *tname;
	char	   *fname;

	/* directory */
	dname = guc_malloc(ERROR, strlen(newval) + 1);	/* runtime dir */
	sprintf(dname, "%s", newval);

	/* global stats */
	tname = guc_malloc(ERROR, strlen(newval) + 12); /* /global.tmp */
	sprintf(tname, "%s/global.tmp", newval);
	fname = guc_malloc(ERROR, strlen(newval) + 13); /* /global.stat */
	sprintf(fname, "%s/global.stat", newval);

	if (pgstat_stat_directory)
		free(pgstat_stat_directory);
	pgstat_stat_directory = dname;
	if (pgstat_stat_tmpname)
		free(pgstat_stat_tmpname);
	pgstat_stat_tmpname = tname;
	if (pgstat_stat_filename)
		free(pgstat_stat_filename);
	pgstat_stat_filename = fname;
}