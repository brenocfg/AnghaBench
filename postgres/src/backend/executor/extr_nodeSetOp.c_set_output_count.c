#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int cmd; } ;
struct TYPE_7__ {scalar_t__ plan; } ;
struct TYPE_9__ {int numOutput; TYPE_1__ ps; } ;
struct TYPE_8__ {int numLeft; int numRight; } ;
typedef  TYPE_2__* SetOpStatePerGroup ;
typedef  TYPE_3__ SetOpState ;
typedef  TYPE_4__ SetOp ;

/* Variables and functions */
 int /*<<< orphan*/  ERROR ; 
#define  SETOPCMD_EXCEPT 131 
#define  SETOPCMD_EXCEPT_ALL 130 
#define  SETOPCMD_INTERSECT 129 
#define  SETOPCMD_INTERSECT_ALL 128 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*,int) ; 

__attribute__((used)) static void
set_output_count(SetOpState *setopstate, SetOpStatePerGroup pergroup)
{
	SetOp	   *plannode = (SetOp *) setopstate->ps.plan;

	switch (plannode->cmd)
	{
		case SETOPCMD_INTERSECT:
			if (pergroup->numLeft > 0 && pergroup->numRight > 0)
				setopstate->numOutput = 1;
			else
				setopstate->numOutput = 0;
			break;
		case SETOPCMD_INTERSECT_ALL:
			setopstate->numOutput =
				(pergroup->numLeft < pergroup->numRight) ?
				pergroup->numLeft : pergroup->numRight;
			break;
		case SETOPCMD_EXCEPT:
			if (pergroup->numLeft > 0 && pergroup->numRight == 0)
				setopstate->numOutput = 1;
			else
				setopstate->numOutput = 0;
			break;
		case SETOPCMD_EXCEPT_ALL:
			setopstate->numOutput =
				(pergroup->numLeft < pergroup->numRight) ?
				0 : (pergroup->numLeft - pergroup->numRight);
			break;
		default:
			elog(ERROR, "unrecognized set op: %d", (int) plannode->cmd);
			break;
	}
}