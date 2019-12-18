#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int /*<<< orphan*/  prorettype; scalar_t__ proretset; } ;
struct TYPE_8__ {int /*<<< orphan*/  len; int /*<<< orphan*/  data; } ;
typedef  TYPE_1__ StringInfoData ;
typedef  int /*<<< orphan*/  StringInfo ;
typedef  int /*<<< orphan*/  HeapTuple ;
typedef  TYPE_2__* Form_pg_proc ;

/* Variables and functions */
 int /*<<< orphan*/  GETSTRUCT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  appendBinaryStringInfo (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  appendStringInfoChar (TYPE_1__*,char) ; 
 int /*<<< orphan*/  appendStringInfoString (TYPE_1__*,char*) ; 
 char* format_type_be (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  initStringInfo (TYPE_1__*) ; 
 int print_function_arguments (TYPE_1__*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  resetStringInfo (TYPE_1__*) ; 

__attribute__((used)) static void
print_function_rettype(StringInfo buf, HeapTuple proctup)
{
	Form_pg_proc proc = (Form_pg_proc) GETSTRUCT(proctup);
	int			ntabargs = 0;
	StringInfoData rbuf;

	initStringInfo(&rbuf);

	if (proc->proretset)
	{
		/* It might be a table function; try to print the arguments */
		appendStringInfoString(&rbuf, "TABLE(");
		ntabargs = print_function_arguments(&rbuf, proctup, true, false);
		if (ntabargs > 0)
			appendStringInfoChar(&rbuf, ')');
		else
			resetStringInfo(&rbuf);
	}

	if (ntabargs == 0)
	{
		/* Not a table function, so do the normal thing */
		if (proc->proretset)
			appendStringInfoString(&rbuf, "SETOF ");
		appendStringInfoString(&rbuf, format_type_be(proc->prorettype));
	}

	appendBinaryStringInfo(buf, rbuf.data, rbuf.len);
}