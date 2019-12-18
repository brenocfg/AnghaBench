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
typedef  int /*<<< orphan*/  SharedFileSet ;

/* Variables and functions */
 int /*<<< orphan*/  CHECK_FOR_INTERRUPTS () ; 
 int /*<<< orphan*/  ERROR ; 
 int MAXPGPATH ; 
 int /*<<< orphan*/  SharedFileSetDelete (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  SharedSegmentName (char*,char const*,int) ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*,char const*) ; 

void
BufFileDeleteShared(SharedFileSet *fileset, const char *name)
{
	char		segment_name[MAXPGPATH];
	int			segment = 0;
	bool		found = false;

	/*
	 * We don't know how many segments the file has.  We'll keep deleting
	 * until we run out.  If we don't manage to find even an initial segment,
	 * raise an error.
	 */
	for (;;)
	{
		SharedSegmentName(segment_name, name, segment);
		if (!SharedFileSetDelete(fileset, segment_name, true))
			break;
		found = true;
		++segment;

		CHECK_FOR_INTERRUPTS();
	}

	if (!found)
		elog(ERROR, "could not delete unknown shared BufFile \"%s\"", name);
}