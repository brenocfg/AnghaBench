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
struct ctlr_info {int /*<<< orphan*/  heartbeat_sample_interval; int /*<<< orphan*/  firmware_flash_in_progress; } ;
struct TYPE_2__ {int /*<<< orphan*/  CDB; } ;
struct CommandList {TYPE_1__ Request; } ;

/* Variables and functions */
 int /*<<< orphan*/  HEARTBEAT_SAMPLE_INTERVAL_DURING_FLASH ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  is_firmware_flash_cmd (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void dial_down_lockup_detection_during_fw_flash(struct ctlr_info *h,
		struct CommandList *c)
{
	if (!is_firmware_flash_cmd(c->Request.CDB))
		return;
	atomic_inc(&h->firmware_flash_in_progress);
	h->heartbeat_sample_interval = HEARTBEAT_SAMPLE_INTERVAL_DURING_FLASH;
}