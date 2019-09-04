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
struct DeviceCtlBlk {size_t target_id; int target_lun; int /*<<< orphan*/  list; struct AdapterCtlBlk* acb; } ;
struct AdapterCtlBlk {int* dcb_map; struct DeviceCtlBlk*** children; int /*<<< orphan*/  dcb_list; struct DeviceCtlBlk* dcb_run_robin; } ;

/* Variables and functions */
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ list_empty (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void adapter_add_device(struct AdapterCtlBlk *acb,
		struct DeviceCtlBlk *dcb)
{
	/* backpointer to adapter */
	dcb->acb = acb;
	
	/* set run_robin to this device if it is currently empty */
	if (list_empty(&acb->dcb_list))
		acb->dcb_run_robin = dcb;

	/* add device to list */
	list_add_tail(&dcb->list, &acb->dcb_list);

	/* update device maps */
	acb->dcb_map[dcb->target_id] |= (1 << dcb->target_lun);
	acb->children[dcb->target_id][dcb->target_lun] = dcb;
}