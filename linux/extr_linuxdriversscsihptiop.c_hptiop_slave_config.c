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
struct scsi_device {scalar_t__ type; int /*<<< orphan*/  request_queue; } ;

/* Variables and functions */
 scalar_t__ TYPE_TAPE ; 
 int /*<<< orphan*/  blk_queue_max_hw_sectors (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int hptiop_slave_config(struct scsi_device *sdev)
{
	if (sdev->type == TYPE_TAPE)
		blk_queue_max_hw_sectors(sdev->request_queue, 8192);

	return 0;
}