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
struct DeviceCtlBlk {int /*<<< orphan*/  srb_going_list; int /*<<< orphan*/  target_lun; int /*<<< orphan*/  target_id; } ;
struct AdapterCtlBlk {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DBG_1 ; 
 int /*<<< orphan*/  adapter_remove_device (struct AdapterCtlBlk*,struct DeviceCtlBlk*) ; 
 int /*<<< orphan*/  dprintkdbg (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  kfree (struct DeviceCtlBlk*) ; 
 int list_size (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void adapter_remove_and_free_device(struct AdapterCtlBlk *acb,
		struct DeviceCtlBlk *dcb)
{
	if (list_size(&dcb->srb_going_list) > 1) {
		dprintkdbg(DBG_1, "adapter_remove_and_free_device: <%02i-%i> "
		           "Won't remove because of %i active requests.\n",
			   dcb->target_id, dcb->target_lun,
			   list_size(&dcb->srb_going_list));
		return;
	}
	adapter_remove_device(acb, dcb);
	kfree(dcb);
}