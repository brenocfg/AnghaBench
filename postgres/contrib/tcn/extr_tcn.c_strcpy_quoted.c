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
typedef  int /*<<< orphan*/  StringInfo ;

/* Variables and functions */
 int /*<<< orphan*/  appendStringInfoCharMacro (int /*<<< orphan*/ ,char const) ; 

__attribute__((used)) static void
strcpy_quoted(StringInfo r, const char *s, const char q)
{
	appendStringInfoCharMacro(r, q);
	while (*s)
	{
		if (*s == q)
			appendStringInfoCharMacro(r, q);
		appendStringInfoCharMacro(r, *s);
		s++;
	}
	appendStringInfoCharMacro(r, q);
}