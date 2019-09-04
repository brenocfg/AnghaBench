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
struct TYPE_3__ {int /*<<< orphan*/  ref_count; int /*<<< orphan*/  nvme_ls_waitq; } ;
typedef  TYPE_1__ srb_t ;

/* Variables and functions */
 int HZ ; 
 int NVME_ABORT_POLLING_PERIOD ; 
 int QLA_FUNCTION_FAILED ; 
 int QLA_SUCCESS ; 
 int atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wait_event_timeout (int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static int qla_nvme_wait_on_command(srb_t *sp)
{
	int ret = QLA_SUCCESS;

	wait_event_timeout(sp->nvme_ls_waitq, (atomic_read(&sp->ref_count) > 1),
	    NVME_ABORT_POLLING_PERIOD*HZ);

	if (atomic_read(&sp->ref_count) > 1)
		ret = QLA_FUNCTION_FAILED;

	return ret;
}