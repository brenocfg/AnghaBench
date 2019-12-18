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
struct TYPE_3__ {int target; } ;
typedef  TYPE_1__ DiscardStmt ;

/* Variables and functions */
#define  DISCARD_ALL 131 
#define  DISCARD_PLANS 130 
#define  DISCARD_SEQUENCES 129 
#define  DISCARD_TEMP 128 
 int /*<<< orphan*/  DiscardAll (int) ; 
 int /*<<< orphan*/  ERROR ; 
 int /*<<< orphan*/  ResetPlanCache () ; 
 int /*<<< orphan*/  ResetSequenceCaches () ; 
 int /*<<< orphan*/  ResetTempTableNamespace () ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*,int) ; 

void
DiscardCommand(DiscardStmt *stmt, bool isTopLevel)
{
	switch (stmt->target)
	{
		case DISCARD_ALL:
			DiscardAll(isTopLevel);
			break;

		case DISCARD_PLANS:
			ResetPlanCache();
			break;

		case DISCARD_SEQUENCES:
			ResetSequenceCaches();
			break;

		case DISCARD_TEMP:
			ResetTempTableNamespace();
			break;

		default:
			elog(ERROR, "unrecognized DISCARD target: %d", stmt->target);
	}
}