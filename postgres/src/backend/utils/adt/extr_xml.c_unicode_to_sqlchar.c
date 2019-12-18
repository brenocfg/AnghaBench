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
typedef  int /*<<< orphan*/  utf8string ;
typedef  int /*<<< orphan*/  pg_wchar ;

/* Variables and functions */
 int /*<<< orphan*/  PG_UTF8 ; 
 int /*<<< orphan*/  memset (char*,int /*<<< orphan*/ ,int) ; 
 char* pg_any_to_server (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 char* pstrdup (char*) ; 
 int /*<<< orphan*/  strlen (char*) ; 
 int /*<<< orphan*/  unicode_to_utf8 (int /*<<< orphan*/ ,unsigned char*) ; 

__attribute__((used)) static char *
unicode_to_sqlchar(pg_wchar c)
{
	char		utf8string[8];	/* need room for trailing zero */
	char	   *result;

	memset(utf8string, 0, sizeof(utf8string));
	unicode_to_utf8(c, (unsigned char *) utf8string);

	result = pg_any_to_server(utf8string, strlen(utf8string), PG_UTF8);
	/* if pg_any_to_server didn't strdup, we must */
	if (result == utf8string)
		result = pstrdup(result);
	return result;
}