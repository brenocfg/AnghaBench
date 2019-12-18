#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int status; int /*<<< orphan*/  xid; } ;
typedef  int /*<<< orphan*/  StringInfo ;
typedef  TYPE_1__ MultiXactMember ;

/* Variables and functions */
#define  MultiXactStatusForKeyShare 133 
#define  MultiXactStatusForNoKeyUpdate 132 
#define  MultiXactStatusForShare 131 
#define  MultiXactStatusForUpdate 130 
#define  MultiXactStatusNoKeyUpdate 129 
#define  MultiXactStatusUpdate 128 
 int /*<<< orphan*/  appendStringInfo (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  appendStringInfoString (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static void
out_member(StringInfo buf, MultiXactMember *member)
{
	appendStringInfo(buf, "%u ", member->xid);
	switch (member->status)
	{
		case MultiXactStatusForKeyShare:
			appendStringInfoString(buf, "(keysh) ");
			break;
		case MultiXactStatusForShare:
			appendStringInfoString(buf, "(sh) ");
			break;
		case MultiXactStatusForNoKeyUpdate:
			appendStringInfoString(buf, "(fornokeyupd) ");
			break;
		case MultiXactStatusForUpdate:
			appendStringInfoString(buf, "(forupd) ");
			break;
		case MultiXactStatusNoKeyUpdate:
			appendStringInfoString(buf, "(nokeyupd) ");
			break;
		case MultiXactStatusUpdate:
			appendStringInfoString(buf, "(upd) ");
			break;
		default:
			appendStringInfoString(buf, "(unk) ");
			break;
	}
}