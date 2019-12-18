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
 char RANGE_EMPTY ; 
 int /*<<< orphan*/  RANGE_EMPTY_LITERAL ; 
 scalar_t__ RANGE_HAS_LBOUND (char) ; 
 scalar_t__ RANGE_HAS_UBOUND (char) ; 
 char RANGE_LB_INC ; 
 char RANGE_UB_INC ; 
 int /*<<< orphan*/  appendStringInfoChar (TYPE_1__*,char) ; 
 int /*<<< orphan*/  appendStringInfoString (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  initStringInfo (TYPE_1__*) ; 
 char* pstrdup (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  range_bound_escape (char const*) ; 

__attribute__((used)) static char *
range_deparse(char flags, const char *lbound_str, const char *ubound_str)
{
	StringInfoData buf;

	if (flags & RANGE_EMPTY)
		return pstrdup(RANGE_EMPTY_LITERAL);

	initStringInfo(&buf);

	appendStringInfoChar(&buf, (flags & RANGE_LB_INC) ? '[' : '(');

	if (RANGE_HAS_LBOUND(flags))
		appendStringInfoString(&buf, range_bound_escape(lbound_str));

	appendStringInfoChar(&buf, ',');

	if (RANGE_HAS_UBOUND(flags))
		appendStringInfoString(&buf, range_bound_escape(ubound_str));

	appendStringInfoChar(&buf, (flags & RANGE_UB_INC) ? ']' : ')');

	return buf.data;
}