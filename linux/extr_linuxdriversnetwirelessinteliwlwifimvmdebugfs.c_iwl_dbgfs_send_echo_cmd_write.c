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
struct iwl_mvm {int /*<<< orphan*/  mutex; } ;
typedef  size_t ssize_t ;
typedef  int /*<<< orphan*/  loff_t ;

/* Variables and functions */
 int /*<<< orphan*/  ECHO_CMD ; 
 size_t EIO ; 
 int /*<<< orphan*/  iwl_mvm_firmware_running (struct iwl_mvm*) ; 
 int iwl_mvm_send_cmd_pdu (struct iwl_mvm*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static ssize_t
iwl_dbgfs_send_echo_cmd_write(struct iwl_mvm *mvm, char *buf,
			      size_t count, loff_t *ppos)
{
	int ret;

	if (!iwl_mvm_firmware_running(mvm))
		return -EIO;

	mutex_lock(&mvm->mutex);
	ret = iwl_mvm_send_cmd_pdu(mvm, ECHO_CMD, 0, 0, NULL);
	mutex_unlock(&mvm->mutex);

	return ret ?: count;
}