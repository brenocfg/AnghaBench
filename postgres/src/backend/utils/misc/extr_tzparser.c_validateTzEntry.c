#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int offset; scalar_t__ abbrev; int /*<<< orphan*/  lineno; int /*<<< orphan*/  filename; } ;
typedef  TYPE_1__ tzEntry ;

/* Variables and functions */
 int /*<<< orphan*/  GUC_check_errmsg (char*,int,scalar_t__,int /*<<< orphan*/ ,...) ; 
 scalar_t__ TOKMAXLEN ; 
 unsigned char pg_tolower (unsigned char) ; 
 scalar_t__ strlen (scalar_t__) ; 

__attribute__((used)) static bool
validateTzEntry(tzEntry *tzentry)
{
	unsigned char *p;

	/*
	 * Check restrictions imposed by datetktbl storage format (see datetime.c)
	 */
	if (strlen(tzentry->abbrev) > TOKMAXLEN)
	{
		GUC_check_errmsg("time zone abbreviation \"%s\" is too long (maximum %d characters) in time zone file \"%s\", line %d",
						 tzentry->abbrev, TOKMAXLEN,
						 tzentry->filename, tzentry->lineno);
		return false;
	}

	/*
	 * Sanity-check the offset: shouldn't exceed 14 hours
	 */
	if (tzentry->offset > 14 * 60 * 60 ||
		tzentry->offset < -14 * 60 * 60)
	{
		GUC_check_errmsg("time zone offset %d is out of range in time zone file \"%s\", line %d",
						 tzentry->offset,
						 tzentry->filename, tzentry->lineno);
		return false;
	}

	/*
	 * Convert abbrev to lowercase (must match datetime.c's conversion)
	 */
	for (p = (unsigned char *) tzentry->abbrev; *p; p++)
		*p = pg_tolower(*p);

	return true;
}