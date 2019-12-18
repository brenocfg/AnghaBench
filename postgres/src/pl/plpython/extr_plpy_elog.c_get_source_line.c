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
 scalar_t__ isspace (unsigned char) ; 
 char* pnstrdup (char const*,int) ; 
 char* pstrdup (char const*) ; 
 char* strchr (char const*,char) ; 

__attribute__((used)) static char *
get_source_line(const char *src, int lineno)
{
	const char *s = NULL;
	const char *next = src;
	int			current = 0;

	/* sanity check */
	if (lineno <= 0)
		return NULL;

	while (current < lineno)
	{
		s = next;
		next = strchr(s + 1, '\n');
		current++;
		if (next == NULL)
			break;
	}

	if (current != lineno)
		return NULL;

	while (*s && isspace((unsigned char) *s))
		s++;

	if (next == NULL)
		return pstrdup(s);

	/*
	 * Sanity check, next < s if the line was all-whitespace, which should
	 * never happen if Python reported a frame created on that line, but check
	 * anyway.
	 */
	if (next < s)
		return NULL;

	return pnstrdup(s, next - s);
}