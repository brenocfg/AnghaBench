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
 int /*<<< orphan*/  ERRCODE_SYNTAX_ERROR ; 
 int /*<<< orphan*/  ERROR ; 
 char RANGE_LB_INC ; 
 char RANGE_UB_INC ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errcode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errhint (char*) ; 
 int /*<<< orphan*/  errmsg (char*) ; 

__attribute__((used)) static char
range_parse_flags(const char *flags_str)
{
	char		flags = 0;

	if (flags_str[0] == '\0' ||
		flags_str[1] == '\0' ||
		flags_str[2] != '\0')
		ereport(ERROR,
				(errcode(ERRCODE_SYNTAX_ERROR),
				 errmsg("invalid range bound flags"),
				 errhint("Valid values are \"[]\", \"[)\", \"(]\", and \"()\".")));

	switch (flags_str[0])
	{
		case '[':
			flags |= RANGE_LB_INC;
			break;
		case '(':
			break;
		default:
			ereport(ERROR,
					(errcode(ERRCODE_SYNTAX_ERROR),
					 errmsg("invalid range bound flags"),
					 errhint("Valid values are \"[]\", \"[)\", \"(]\", and \"()\".")));
	}

	switch (flags_str[1])
	{
		case ']':
			flags |= RANGE_UB_INC;
			break;
		case ')':
			break;
		default:
			ereport(ERROR,
					(errcode(ERRCODE_SYNTAX_ERROR),
					 errmsg("invalid range bound flags"),
					 errhint("Valid values are \"[]\", \"[)\", \"(]\", and \"()\".")));
	}

	return flags;
}