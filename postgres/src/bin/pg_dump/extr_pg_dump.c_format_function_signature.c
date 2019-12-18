#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int /*<<< orphan*/  name; } ;
struct TYPE_11__ {int nargs; int /*<<< orphan*/ * argtypes; TYPE_1__ dobj; } ;
struct TYPE_10__ {char* data; } ;
typedef  TYPE_2__ PQExpBufferData ;
typedef  TYPE_3__ FuncInfo ;
typedef  int /*<<< orphan*/  Archive ;

/* Variables and functions */
 int /*<<< orphan*/  appendPQExpBuffer (TYPE_2__*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  appendPQExpBufferChar (TYPE_2__*,char) ; 
 int /*<<< orphan*/  appendPQExpBufferStr (TYPE_2__*,char*) ; 
 int /*<<< orphan*/  fmtId (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (char*) ; 
 char* getFormattedTypeName (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  initPQExpBuffer (TYPE_2__*) ; 
 int /*<<< orphan*/  zeroAsOpaque ; 

__attribute__((used)) static char *
format_function_signature(Archive *fout, FuncInfo *finfo, bool honor_quotes)
{
	PQExpBufferData fn;
	int			j;

	initPQExpBuffer(&fn);
	if (honor_quotes)
		appendPQExpBuffer(&fn, "%s(", fmtId(finfo->dobj.name));
	else
		appendPQExpBuffer(&fn, "%s(", finfo->dobj.name);
	for (j = 0; j < finfo->nargs; j++)
	{
		char	   *typname;

		if (j > 0)
			appendPQExpBufferStr(&fn, ", ");

		typname = getFormattedTypeName(fout, finfo->argtypes[j],
									   zeroAsOpaque);
		appendPQExpBufferStr(&fn, typname);
		free(typname);
	}
	appendPQExpBufferChar(&fn, ')');
	return fn.data;
}