#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct esas2r_request {scalar_t__ req_stat; TYPE_2__* vrq; scalar_t__ interrupt_cx; } ;
struct esas2r_ioctl_fs {scalar_t__ driver_error; int /*<<< orphan*/  status; } ;
struct esas2r_adapter {int dummy; } ;
struct TYPE_3__ {scalar_t__ sub_func; } ;
struct TYPE_4__ {TYPE_1__ flash; } ;

/* Variables and functions */
 int /*<<< orphan*/  ATTO_STS_FAILED ; 
 int /*<<< orphan*/  ATTO_STS_SUCCESS ; 
 scalar_t__ RS_SUCCESS ; 
 scalar_t__ VDA_FLASH_COMMIT ; 
 int /*<<< orphan*/  esas2r_enable_heartbeat (struct esas2r_adapter*) ; 

__attribute__((used)) static void esas2r_complete_fs_ioctl(struct esas2r_adapter *a,
				     struct esas2r_request *rq)
{
	struct esas2r_ioctl_fs *fs =
		(struct esas2r_ioctl_fs *)rq->interrupt_cx;

	if (rq->vrq->flash.sub_func == VDA_FLASH_COMMIT)
		esas2r_enable_heartbeat(a);

	fs->driver_error = rq->req_stat;

	if (fs->driver_error == RS_SUCCESS)
		fs->status = ATTO_STS_SUCCESS;
	else
		fs->status = ATTO_STS_FAILED;
}