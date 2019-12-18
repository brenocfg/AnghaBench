#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {char* data; } ;
typedef  TYPE_1__ StringInfoData ;

/* Variables and functions */
 int /*<<< orphan*/  appendStringInfoCharMacro (TYPE_1__*,char const) ; 
 int /*<<< orphan*/  appendStringInfoString (TYPE_1__*,char*) ; 
 int /*<<< orphan*/  initStringInfo (TYPE_1__*) ; 

char *
escape_xml(const char *str)
{
	StringInfoData buf;
	const char *p;

	initStringInfo(&buf);
	for (p = str; *p; p++)
	{
		switch (*p)
		{
			case '&':
				appendStringInfoString(&buf, "&amp;");
				break;
			case '<':
				appendStringInfoString(&buf, "&lt;");
				break;
			case '>':
				appendStringInfoString(&buf, "&gt;");
				break;
			case '\r':
				appendStringInfoString(&buf, "&#x0d;");
				break;
			default:
				appendStringInfoCharMacro(&buf, *p);
				break;
		}
	}
	return buf.data;
}