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
struct scsi_device {TYPE_1__* host; } ;
struct TYPE_2__ {int /*<<< orphan*/  use_blk_mq; } ;

/* Variables and functions */
 int /*<<< orphan*/  WARN_ON_ONCE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msleep (int) ; 
 scalar_t__ scsi_request_fn_active (struct scsi_device*) ; 

__attribute__((used)) static void scsi_wait_for_queuecommand(struct scsi_device *sdev)
{
	WARN_ON_ONCE(sdev->host->use_blk_mq);

	while (scsi_request_fn_active(sdev))
		msleep(20);
}