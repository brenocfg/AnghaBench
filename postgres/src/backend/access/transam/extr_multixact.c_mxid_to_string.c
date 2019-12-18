#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/  status; int /*<<< orphan*/  xid; } ;
struct TYPE_7__ {char* data; } ;
typedef  TYPE_1__ StringInfoData ;
typedef  TYPE_2__ MultiXactMember ;
typedef  int /*<<< orphan*/  MultiXactId ;

/* Variables and functions */
 char* MemoryContextStrdup (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  TopMemoryContext ; 
 int /*<<< orphan*/  appendStringInfo (TYPE_1__*,char*,int /*<<< orphan*/ ,int,...) ; 
 int /*<<< orphan*/  appendStringInfoChar (TYPE_1__*,char) ; 
 int /*<<< orphan*/  initStringInfo (TYPE_1__*) ; 
 int /*<<< orphan*/  mxstatus_to_string (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pfree (char*) ; 

char *
mxid_to_string(MultiXactId multi, int nmembers, MultiXactMember *members)
{
	static char *str = NULL;
	StringInfoData buf;
	int			i;

	if (str != NULL)
		pfree(str);

	initStringInfo(&buf);

	appendStringInfo(&buf, "%u %d[%u (%s)", multi, nmembers, members[0].xid,
					 mxstatus_to_string(members[0].status));

	for (i = 1; i < nmembers; i++)
		appendStringInfo(&buf, ", %u (%s)", members[i].xid,
						 mxstatus_to_string(members[i].status));

	appendStringInfoChar(&buf, ']');
	str = MemoryContextStrdup(TopMemoryContext, buf.data);
	pfree(buf.data);
	return str;
}