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
typedef  int /*<<< orphan*/  tzEntry ;
typedef  int /*<<< orphan*/  TimeZoneAbbrevTable ;
typedef  int /*<<< orphan*/  MemoryContext ;

/* Variables and functions */
 int /*<<< orphan*/  ALLOCSET_SMALL_SIZES ; 
 int /*<<< orphan*/  AllocSetContextCreate (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * ConvertTimeZoneAbbrevs (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  CurrentMemoryContext ; 
 int /*<<< orphan*/  GUC_check_errmsg (char*) ; 
 int /*<<< orphan*/  MemoryContextDelete (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MemoryContextSwitchTo (int /*<<< orphan*/ ) ; 
 int ParseTzFile (char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ **,int*,int /*<<< orphan*/ ) ; 
 scalar_t__ palloc (int) ; 

TimeZoneAbbrevTable *
load_tzoffsets(const char *filename)
{
	TimeZoneAbbrevTable *result = NULL;
	MemoryContext tmpContext;
	MemoryContext oldContext;
	tzEntry    *array;
	int			arraysize;
	int			n;

	/*
	 * Create a temp memory context to work in.  This makes it easy to clean
	 * up afterwards.
	 */
	tmpContext = AllocSetContextCreate(CurrentMemoryContext,
									   "TZParserMemory",
									   ALLOCSET_SMALL_SIZES);
	oldContext = MemoryContextSwitchTo(tmpContext);

	/* Initialize array at a reasonable size */
	arraysize = 128;
	array = (tzEntry *) palloc(arraysize * sizeof(tzEntry));

	/* Parse the file(s) */
	n = ParseTzFile(filename, 0, &array, &arraysize, 0);

	/* If no errors so far, let datetime.c allocate memory & convert format */
	if (n >= 0)
	{
		result = ConvertTimeZoneAbbrevs(array, n);
		if (!result)
			GUC_check_errmsg("out of memory");
	}

	/* Clean up */
	MemoryContextSwitchTo(oldContext);
	MemoryContextDelete(tmpContext);

	return result;
}