#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {char* name; } ;
struct TYPE_11__ {int nargs; int /*<<< orphan*/ * argtypes; TYPE_1__ dobj; } ;
struct TYPE_13__ {TYPE_2__ aggfn; } ;
struct TYPE_12__ {char* data; } ;
typedef  TYPE_3__ PQExpBufferData ;
typedef  int /*<<< orphan*/  Archive ;
typedef  TYPE_4__ AggInfo ;

/* Variables and functions */
 int /*<<< orphan*/  appendPQExpBuffer (TYPE_3__*,char*,char*,char*) ; 
 int /*<<< orphan*/  appendPQExpBufferChar (TYPE_3__*,char) ; 
 int /*<<< orphan*/  appendPQExpBufferStr (TYPE_3__*,char*) ; 
 char* fmtId (char*) ; 
 int /*<<< orphan*/  free (char*) ; 
 char* getFormattedTypeName (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  initPQExpBuffer (TYPE_3__*) ; 
 int /*<<< orphan*/  zeroAsOpaque ; 

__attribute__((used)) static char *
format_aggregate_signature(AggInfo *agginfo, Archive *fout, bool honor_quotes)
{
	PQExpBufferData buf;
	int			j;

	initPQExpBuffer(&buf);
	if (honor_quotes)
		appendPQExpBufferStr(&buf, fmtId(agginfo->aggfn.dobj.name));
	else
		appendPQExpBufferStr(&buf, agginfo->aggfn.dobj.name);

	if (agginfo->aggfn.nargs == 0)
		appendPQExpBufferStr(&buf, "(*)");
	else
	{
		appendPQExpBufferChar(&buf, '(');
		for (j = 0; j < agginfo->aggfn.nargs; j++)
		{
			char	   *typname;

			typname = getFormattedTypeName(fout, agginfo->aggfn.argtypes[j],
										   zeroAsOpaque);

			appendPQExpBuffer(&buf, "%s%s",
							  (j > 0) ? ", " : "",
							  typname);
			free(typname);
		}
		appendPQExpBufferChar(&buf, ')');
	}
	return buf.data;
}