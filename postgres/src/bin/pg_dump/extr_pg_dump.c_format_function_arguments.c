#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/  name; } ;
struct TYPE_10__ {scalar_t__ nargs; TYPE_1__ dobj; } ;
struct TYPE_9__ {char* data; } ;
typedef  TYPE_2__ PQExpBufferData ;
typedef  TYPE_3__ FuncInfo ;

/* Variables and functions */
 int /*<<< orphan*/  appendPQExpBuffer (TYPE_2__*,char*,char*) ; 
 int /*<<< orphan*/  appendPQExpBufferStr (TYPE_2__*,char*) ; 
 char* fmtId (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  initPQExpBuffer (TYPE_2__*) ; 

__attribute__((used)) static char *
format_function_arguments(FuncInfo *finfo, char *funcargs, bool is_agg)
{
	PQExpBufferData fn;

	initPQExpBuffer(&fn);
	appendPQExpBufferStr(&fn, fmtId(finfo->dobj.name));
	if (is_agg && finfo->nargs == 0)
		appendPQExpBufferStr(&fn, "(*)");
	else
		appendPQExpBuffer(&fn, "(%s)", funcargs);
	return fn.data;
}