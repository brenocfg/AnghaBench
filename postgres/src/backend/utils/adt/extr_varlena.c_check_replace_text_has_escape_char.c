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
typedef  int /*<<< orphan*/  text ;

/* Variables and functions */
 char* VARDATA_ANY (int /*<<< orphan*/  const*) ; 
 int VARSIZE_ANY_EXHDR (int /*<<< orphan*/  const*) ; 
 int pg_database_encoding_max_length () ; 
 int /*<<< orphan*/  pg_mblen (char const*) ; 

__attribute__((used)) static bool
check_replace_text_has_escape_char(const text *replace_text)
{
	const char *p = VARDATA_ANY(replace_text);
	const char *p_end = p + VARSIZE_ANY_EXHDR(replace_text);

	if (pg_database_encoding_max_length() == 1)
	{
		for (; p < p_end; p++)
		{
			if (*p == '\\')
				return true;
		}
	}
	else
	{
		for (; p < p_end; p += pg_mblen(p))
		{
			if (*p == '\\')
				return true;
		}
	}

	return false;
}