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
 void* nodeRead (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 char const* pg_strtok_ptr ; 
 int restore_location_fields ; 

__attribute__((used)) static void *
stringToNodeInternal(const char *str, bool restore_loc_fields)
{
	void	   *retval;
	const char *save_strtok;
#ifdef WRITE_READ_PARSE_PLAN_TREES
	bool		save_restore_location_fields;
#endif

	/*
	 * We save and restore the pre-existing state of pg_strtok. This makes the
	 * world safe for re-entrant invocation of stringToNode, without incurring
	 * a lot of notational overhead by having to pass the next-character
	 * pointer around through all the readfuncs.c code.
	 */
	save_strtok = pg_strtok_ptr;

	pg_strtok_ptr = str;		/* point pg_strtok at the string to read */

	/*
	 * If enabled, likewise save/restore the location field handling flag.
	 */
#ifdef WRITE_READ_PARSE_PLAN_TREES
	save_restore_location_fields = restore_location_fields;
	restore_location_fields = restore_loc_fields;
#endif

	retval = nodeRead(NULL, 0); /* do the reading */

	pg_strtok_ptr = save_strtok;

#ifdef WRITE_READ_PARSE_PLAN_TREES
	restore_location_fields = save_restore_location_fields;
#endif

	return retval;
}