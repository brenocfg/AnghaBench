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

__attribute__((used)) static int tcm_loop_slave_alloc(struct scsi_device *sd)
{
	blk_queue_flag_set(QUEUE_FLAG_BIDI, sd->request_queue);
	return 0;
}