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
 int /*<<< orphan*/  appendStringInfo (TYPE_1__*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  appendStringInfoString (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  initStringInfo (TYPE_1__*) ; 
 int /*<<< orphan*/  quote_identifier (char const*) ; 

char *
quote_qualified_identifier(const char *qualifier,
						   const char *ident)
{
	StringInfoData buf;

	initStringInfo(&buf);
	if (qualifier)
		appendStringInfo(&buf, "%s.", quote_identifier(qualifier));
	appendStringInfoString(&buf, quote_identifier(ident));
	return buf.data;
}