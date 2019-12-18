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
 int atoi (char*) ; 
 scalar_t__ isascii (unsigned char) ; 
 scalar_t__ isdigit (unsigned char) ; 
 scalar_t__ isspace (unsigned char) ; 
 int /*<<< orphan*/  pg_log_error (char*,char*) ; 
 int strlen (char*) ; 

__attribute__((used)) static int
strip_lineno_from_objdesc(char *obj)
{
	char	   *c;
	int			lineno;

	if (!obj || obj[0] == '\0')
		return -1;

	c = obj + strlen(obj) - 1;

	/*
	 * This business of parsing backwards is dangerous as can be in a
	 * multibyte environment: there is no reason to believe that we are
	 * looking at the first byte of a character, nor are we necessarily
	 * working in a "safe" encoding.  Fortunately the bitpatterns we are
	 * looking for are unlikely to occur as non-first bytes, but beware of
	 * trying to expand the set of cases that can be recognized.  We must
	 * guard the <ctype.h> macros by using isascii() first, too.
	 */

	/* skip trailing whitespace */
	while (c > obj && isascii((unsigned char) *c) && isspace((unsigned char) *c))
		c--;

	/* must have a digit as last non-space char */
	if (c == obj || !isascii((unsigned char) *c) || !isdigit((unsigned char) *c))
		return -1;

	/* find start of digit string */
	while (c > obj && isascii((unsigned char) *c) && isdigit((unsigned char) *c))
		c--;

	/* digits must be separated from object name by space or closing paren */
	/* notice also that we are not allowing an empty object name ... */
	if (c == obj || !isascii((unsigned char) *c) ||
		!(isspace((unsigned char) *c) || *c == ')'))
		return -1;

	/* parse digit string */
	c++;
	lineno = atoi(c);
	if (lineno < 1)
	{
		pg_log_error("invalid line number: %s", c);
		return 0;
	}

	/* strip digit string from object name */
	*c = '\0';

	return lineno;
}