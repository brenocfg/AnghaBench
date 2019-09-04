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
struct scsi_device {int /*<<< orphan*/  request_queue; } ;

/* Variables and functions */
 int /*<<< orphan*/  QUEUE_FLAG_BIDI ; 
 int /*<<< orphan*/  blk_queue_flag_set (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int iscsi_sw_tcp_slave_alloc(struct scsi_device *sdev)
{
	blk_queue_flag_set(QUEUE_FLAG_BIDI, sdev->request_queue);
	return 0;
}