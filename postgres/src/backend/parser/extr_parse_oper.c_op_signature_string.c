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
struct TYPE_5__ {char const* data; } ;
typedef  TYPE_1__ StringInfoData ;
typedef  int /*<<< orphan*/  Oid ;
typedef  int /*<<< orphan*/  List ;

/* Variables and functions */
 int /*<<< orphan*/  NameListToString (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  appendStringInfo (TYPE_1__*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  appendStringInfoString (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  format_type_be (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  initStringInfo (TYPE_1__*) ; 

__attribute__((used)) static const char *
op_signature_string(List *op, char oprkind, Oid arg1, Oid arg2)
{
	StringInfoData argbuf;

	initStringInfo(&argbuf);

	if (oprkind != 'l')
		appendStringInfo(&argbuf, "%s ", format_type_be(arg1));

	appendStringInfoString(&argbuf, NameListToString(op));

	if (oprkind != 'r')
		appendStringInfo(&argbuf, " %s", format_type_be(arg2));

	return argbuf.data;			/* return palloc'd string buffer */
}