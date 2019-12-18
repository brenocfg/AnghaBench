#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  trig_delete_instead_row; int /*<<< orphan*/  trig_update_instead_row; int /*<<< orphan*/  trig_insert_instead_row; } ;
typedef  TYPE_1__ TriggerDesc ;
struct TYPE_5__ {TYPE_1__* trigdesc; } ;
typedef  TYPE_2__* Relation ;
typedef  int CmdType ;

/* Variables and functions */
#define  CMD_DELETE 130 
#define  CMD_INSERT 129 
#define  CMD_UPDATE 128 
 int /*<<< orphan*/  ERROR ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*,int) ; 

__attribute__((used)) static bool
view_has_instead_trigger(Relation view, CmdType event)
{
	TriggerDesc *trigDesc = view->trigdesc;

	switch (event)
	{
		case CMD_INSERT:
			if (trigDesc && trigDesc->trig_insert_instead_row)
				return true;
			break;
		case CMD_UPDATE:
			if (trigDesc && trigDesc->trig_update_instead_row)
				return true;
			break;
		case CMD_DELETE:
			if (trigDesc && trigDesc->trig_delete_instead_row)
				return true;
			break;
		default:
			elog(ERROR, "unrecognized CmdType: %d", (int) event);
			break;
	}
	return false;
}