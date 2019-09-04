#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  wait_queue_head_t ;
struct TYPE_2__ {int /*<<< orphan*/  notifyresult_handle; int /*<<< orphan*/  notify_handle; } ;
struct uiscmdrsp {TYPE_1__ scsitaskmgmt; } ;
struct idr {int dummy; } ;

/* Variables and functions */
 void* idr_find (struct idr*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_debug (char*,int) ; 
 int /*<<< orphan*/  pr_err (char*) ; 
 scalar_t__ unlikely (int) ; 
 int /*<<< orphan*/  wake_up_all (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void complete_taskmgmt_command(struct idr *idrtable,
				      struct uiscmdrsp *cmdrsp, int result)
{
	wait_queue_head_t *wq =
		idr_find(idrtable, cmdrsp->scsitaskmgmt.notify_handle);
	int *scsi_result_ptr =
		idr_find(idrtable, cmdrsp->scsitaskmgmt.notifyresult_handle);
	if (unlikely(!(wq && scsi_result_ptr))) {
		pr_err("visorhba: no completion context; cmd will time out\n");
		return;
	}

	/* copy the result of the taskmgmt and
	 * wake up the error handler that is waiting for this
	 */
	pr_debug("visorhba: notifying initiator with result=0x%x\n", result);
	*scsi_result_ptr = result;
	wake_up_all(wq);
}