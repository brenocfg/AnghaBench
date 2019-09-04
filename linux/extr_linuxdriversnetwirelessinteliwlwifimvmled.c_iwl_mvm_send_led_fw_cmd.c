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
struct iwl_mvm {int dummy; } ;
struct iwl_led_cmd {int /*<<< orphan*/  status; } ;
struct iwl_host_cmd {int /*<<< orphan*/  flags; int /*<<< orphan*/  data; int /*<<< orphan*/  len; int /*<<< orphan*/  id; } ;

/* Variables and functions */
 int /*<<< orphan*/  CMD_ASYNC ; 
 int /*<<< orphan*/  IWL_WARN (struct iwl_mvm*,char*,int) ; 
 int /*<<< orphan*/  LEDS_CMD ; 
 int /*<<< orphan*/  LONG_GROUP ; 
 int /*<<< orphan*/  WIDE_ID (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpu_to_le32 (int) ; 
 int /*<<< orphan*/  iwl_mvm_firmware_running (struct iwl_mvm*) ; 
 int iwl_mvm_send_cmd (struct iwl_mvm*,struct iwl_host_cmd*) ; 

__attribute__((used)) static void iwl_mvm_send_led_fw_cmd(struct iwl_mvm *mvm, bool on)
{
	struct iwl_led_cmd led_cmd = {
		.status = cpu_to_le32(on),
	};
	struct iwl_host_cmd cmd = {
		.id = WIDE_ID(LONG_GROUP, LEDS_CMD),
		.len = { sizeof(led_cmd), },
		.data = { &led_cmd, },
		.flags = CMD_ASYNC,
	};
	int err;

	if (!iwl_mvm_firmware_running(mvm))
		return;

	err = iwl_mvm_send_cmd(mvm, &cmd);

	if (err)
		IWL_WARN(mvm, "LED command failed: %d\n", err);
}