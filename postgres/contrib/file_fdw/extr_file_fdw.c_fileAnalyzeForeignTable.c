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
struct stat {int st_size; } ;
typedef  int /*<<< orphan*/  Relation ;
typedef  int /*<<< orphan*/  List ;
typedef  int BlockNumber ;
typedef  int /*<<< orphan*/  AcquireSampleRowsFunc ;

/* Variables and functions */
 int BLCKSZ ; 
 int /*<<< orphan*/  ERROR ; 
 int /*<<< orphan*/  RelationGetRelid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errcode_for_file_access () ; 
 int /*<<< orphan*/  errmsg (char*,char*) ; 
 int /*<<< orphan*/  fileGetOptions (int /*<<< orphan*/ ,char**,int*,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  file_acquire_sample_rows ; 
 scalar_t__ stat (char*,struct stat*) ; 

__attribute__((used)) static bool
fileAnalyzeForeignTable(Relation relation,
						AcquireSampleRowsFunc *func,
						BlockNumber *totalpages)
{
	char	   *filename;
	bool		is_program;
	List	   *options;
	struct stat stat_buf;

	/* Fetch options of foreign table */
	fileGetOptions(RelationGetRelid(relation), &filename, &is_program, &options);

	/*
	 * If this is a program instead of a file, just return false to skip
	 * analyzing the table.  We could run the program and collect stats on
	 * whatever it currently returns, but it seems likely that in such cases
	 * the output would be too volatile for the stats to be useful.  Maybe
	 * there should be an option to enable doing this?
	 */
	if (is_program)
		return false;

	/*
	 * Get size of the file.  (XXX if we fail here, would it be better to just
	 * return false to skip analyzing the table?)
	 */
	if (stat(filename, &stat_buf) < 0)
		ereport(ERROR,
				(errcode_for_file_access(),
				 errmsg("could not stat file \"%s\": %m",
						filename)));

	/*
	 * Convert size to pages.  Must return at least 1 so that we can tell
	 * later on that pg_class.relpages is not default.
	 */
	*totalpages = (stat_buf.st_size + (BLCKSZ - 1)) / BLCKSZ;
	if (*totalpages < 1)
		*totalpages = 1;

	*func = file_acquire_sample_rows;

	return true;
}