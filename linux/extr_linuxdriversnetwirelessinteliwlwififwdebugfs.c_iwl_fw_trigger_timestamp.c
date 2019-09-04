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
typedef  int u32 ;
struct TYPE_2__ {int /*<<< orphan*/  delay; int /*<<< orphan*/  wk; } ;
struct iwl_fw_runtime {TYPE_1__ timestamp; } ;

/* Variables and functions */
 int /*<<< orphan*/  IWL_INFO (struct iwl_fw_runtime*,char*,int) ; 
 int /*<<< orphan*/  iwl_fw_cancel_timestamp (struct iwl_fw_runtime*) ; 
 int /*<<< orphan*/  msecs_to_jiffies (int) ; 
 int /*<<< orphan*/  round_jiffies_relative (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  schedule_delayed_work (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void iwl_fw_trigger_timestamp(struct iwl_fw_runtime *fwrt, u32 delay)
{
	IWL_INFO(fwrt,
		 "starting timestamp_marker trigger with delay: %us\n",
		 delay);

	iwl_fw_cancel_timestamp(fwrt);

	fwrt->timestamp.delay = msecs_to_jiffies(delay * 1000);

	schedule_delayed_work(&fwrt->timestamp.wk,
			      round_jiffies_relative(fwrt->timestamp.delay));
}