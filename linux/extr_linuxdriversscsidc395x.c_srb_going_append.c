#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct ScsiReqBlk {int /*<<< orphan*/  list; int /*<<< orphan*/  cmd; } ;
struct DeviceCtlBlk {int /*<<< orphan*/  srb_going_list; int /*<<< orphan*/  target_lun; int /*<<< orphan*/  target_id; } ;

/* Variables and functions */
 int /*<<< orphan*/  DBG_0 ; 
 int /*<<< orphan*/  dprintkdbg (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct ScsiReqBlk*) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void srb_going_append(struct DeviceCtlBlk *dcb, struct ScsiReqBlk *srb)
{
	dprintkdbg(DBG_0, "srb_going_append: (0x%p) <%02i-%i> srb=%p\n",
		srb->cmd, dcb->target_id, dcb->target_lun, srb);
	list_add_tail(&srb->list, &dcb->srb_going_list);
}