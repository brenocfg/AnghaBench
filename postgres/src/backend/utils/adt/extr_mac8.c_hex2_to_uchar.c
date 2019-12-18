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
 int /*<<< orphan*/  ERRCODE_INVALID_TEXT_REPRESENTATION ; 
 int /*<<< orphan*/  ERROR ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errcode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errmsg (char*,char*,unsigned char const*) ; 
 char* hexlookup ; 

__attribute__((used)) static inline unsigned char
hex2_to_uchar(const unsigned char *ptr, const unsigned char *str)
{
	unsigned char ret = 0;
	signed char lookup;

	/* Handle the first character */
	if (*ptr > 127)
		goto invalid_input;

	lookup = hexlookup[*ptr];
	if (lookup < 0)
		goto invalid_input;

	ret = lookup << 4;

	/* Move to the second character */
	ptr++;

	if (*ptr > 127)
		goto invalid_input;

	lookup = hexlookup[*ptr];
	if (lookup < 0)
		goto invalid_input;

	ret += lookup;

	return ret;

invalid_input:
	ereport(ERROR,
			(errcode(ERRCODE_INVALID_TEXT_REPRESENTATION),
			 errmsg("invalid input syntax for type %s: \"%s\"", "macaddr8",
					str)));

	/* We do not actually reach here */
	return 0;
}