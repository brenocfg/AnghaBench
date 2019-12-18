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
 int /*<<< orphan*/  appendBinaryStringInfo (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  appendStringInfoCharMacro (int /*<<< orphan*/ ,char) ; 

__attribute__((used)) static void
add_indent(StringInfo out, bool indent, int level)
{
	if (indent)
	{
		int			i;

		appendStringInfoCharMacro(out, '\n');
		for (i = 0; i < level; i++)
			appendBinaryStringInfo(out, "    ", 4);
	}
}