#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {char const* data; } ;
typedef  TYPE_1__ StringInfoData ;
typedef  int /*<<< orphan*/  Oid ;
typedef  int /*<<< orphan*/  ListCell ;
typedef  int /*<<< orphan*/  List ;

/* Variables and functions */
 int /*<<< orphan*/  appendStringInfo (TYPE_1__*,char*,char const*) ; 
 int /*<<< orphan*/  appendStringInfoChar (TYPE_1__*,char) ; 
 int /*<<< orphan*/  appendStringInfoString (TYPE_1__*,char*) ; 
 char* format_type_be (int /*<<< orphan*/  const) ; 
 int /*<<< orphan*/  initStringInfo (TYPE_1__*) ; 
 scalar_t__ lfirst (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * list_head (int /*<<< orphan*/ *) ; 
 int list_length (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * lnext (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

const char *
funcname_signature_string(const char *funcname, int nargs,
						  List *argnames, const Oid *argtypes)
{
	StringInfoData argbuf;
	int			numposargs;
	ListCell   *lc;
	int			i;

	initStringInfo(&argbuf);

	appendStringInfo(&argbuf, "%s(", funcname);

	numposargs = nargs - list_length(argnames);
	lc = list_head(argnames);

	for (i = 0; i < nargs; i++)
	{
		if (i)
			appendStringInfoString(&argbuf, ", ");
		if (i >= numposargs)
		{
			appendStringInfo(&argbuf, "%s => ", (char *) lfirst(lc));
			lc = lnext(argnames, lc);
		}
		appendStringInfoString(&argbuf, format_type_be(argtypes[i]));
	}

	appendStringInfoChar(&argbuf, ')');

	return argbuf.data;			/* return palloc'd string buffer */
}