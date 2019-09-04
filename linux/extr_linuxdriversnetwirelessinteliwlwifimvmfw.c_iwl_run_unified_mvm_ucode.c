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
typedef  int /*<<< orphan*/  u16 ;
struct iwl_nvm_access_complete_cmd {int /*<<< orphan*/  init_flags; } ;
struct iwl_notification_wait {int dummy; } ;
struct iwl_mvm {int /*<<< orphan*/  notif_wait; int /*<<< orphan*/ * nvm_data; int /*<<< orphan*/  fw; int /*<<< orphan*/  trans; int /*<<< orphan*/  nvm_sections; scalar_t__ nvm_file_name; int /*<<< orphan*/  mutex; } ;
struct iwl_init_extended_cfg_cmd {int /*<<< orphan*/  init_flags; } ;
typedef  int /*<<< orphan*/  nvm_complete ;
typedef  int /*<<< orphan*/  init_cfg ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  BIT (int /*<<< orphan*/ ) ; 
#define  INIT_COMPLETE_NOTIF 128 
 int /*<<< orphan*/  INIT_EXTENDED_CFG_CMD ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IWL_ERR (struct iwl_mvm*,char*,int) ; 
 int /*<<< orphan*/  IWL_INIT_NVM ; 
 scalar_t__ IWL_MVM_PARSE_NVM ; 
 int /*<<< orphan*/  IWL_UCODE_REGULAR ; 
 int /*<<< orphan*/  MVM_UCODE_ALIVE_TIMEOUT ; 
 int /*<<< orphan*/  NVM_ACCESS_COMPLETE ; 
 int PTR_ERR (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  REGULATORY_AND_NVM_GROUP ; 
 int /*<<< orphan*/  SYSTEM_GROUP ; 
 int /*<<< orphan*/  WIDE_ID (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpu_to_le32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * iwl_get_nvm (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iwl_init_notification_wait (int /*<<< orphan*/ *,struct iwl_notification_wait*,int /*<<< orphan*/  const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  iwl_mvm_load_nvm_to_nic (struct iwl_mvm*) ; 
 int iwl_mvm_load_ucode_wait_alive (struct iwl_mvm*,int /*<<< orphan*/ ) ; 
 int iwl_mvm_send_cmd_pdu (struct iwl_mvm*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,struct iwl_nvm_access_complete_cmd*) ; 
 int iwl_nvm_init (struct iwl_mvm*) ; 
 int /*<<< orphan*/  iwl_read_external_nvm (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iwl_remove_notification (int /*<<< orphan*/ *,struct iwl_notification_wait*) ; 
 int /*<<< orphan*/  iwl_wait_init_complete ; 
 int iwl_wait_notification (int /*<<< orphan*/ *,struct iwl_notification_wait*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lockdep_assert_held (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int iwl_run_unified_mvm_ucode(struct iwl_mvm *mvm, bool read_nvm)
{
	struct iwl_notification_wait init_wait;
	struct iwl_nvm_access_complete_cmd nvm_complete = {};
	struct iwl_init_extended_cfg_cmd init_cfg = {
		.init_flags = cpu_to_le32(BIT(IWL_INIT_NVM)),
	};
	static const u16 init_complete[] = {
		INIT_COMPLETE_NOTIF,
	};
	int ret;

	lockdep_assert_held(&mvm->mutex);

	iwl_init_notification_wait(&mvm->notif_wait,
				   &init_wait,
				   init_complete,
				   ARRAY_SIZE(init_complete),
				   iwl_wait_init_complete,
				   NULL);

	/* Will also start the device */
	ret = iwl_mvm_load_ucode_wait_alive(mvm, IWL_UCODE_REGULAR);
	if (ret) {
		IWL_ERR(mvm, "Failed to start RT ucode: %d\n", ret);
		goto error;
	}

	/* Send init config command to mark that we are sending NVM access
	 * commands
	 */
	ret = iwl_mvm_send_cmd_pdu(mvm, WIDE_ID(SYSTEM_GROUP,
						INIT_EXTENDED_CFG_CMD), 0,
				   sizeof(init_cfg), &init_cfg);
	if (ret) {
		IWL_ERR(mvm, "Failed to run init config command: %d\n",
			ret);
		goto error;
	}

	/* Load NVM to NIC if needed */
	if (mvm->nvm_file_name) {
		iwl_read_external_nvm(mvm->trans, mvm->nvm_file_name,
				      mvm->nvm_sections);
		iwl_mvm_load_nvm_to_nic(mvm);
	}

	if (IWL_MVM_PARSE_NVM && read_nvm) {
		ret = iwl_nvm_init(mvm);
		if (ret) {
			IWL_ERR(mvm, "Failed to read NVM: %d\n", ret);
			goto error;
		}
	}

	ret = iwl_mvm_send_cmd_pdu(mvm, WIDE_ID(REGULATORY_AND_NVM_GROUP,
						NVM_ACCESS_COMPLETE), 0,
				   sizeof(nvm_complete), &nvm_complete);
	if (ret) {
		IWL_ERR(mvm, "Failed to run complete NVM access: %d\n",
			ret);
		goto error;
	}

	/* We wait for the INIT complete notification */
	ret = iwl_wait_notification(&mvm->notif_wait, &init_wait,
				    MVM_UCODE_ALIVE_TIMEOUT);
	if (ret)
		return ret;

	/* Read the NVM only at driver load time, no need to do this twice */
	if (!IWL_MVM_PARSE_NVM && read_nvm) {
		mvm->nvm_data = iwl_get_nvm(mvm->trans, mvm->fw);
		if (IS_ERR(mvm->nvm_data)) {
			ret = PTR_ERR(mvm->nvm_data);
			mvm->nvm_data = NULL;
			IWL_ERR(mvm, "Failed to read NVM: %d\n", ret);
			return ret;
		}
	}

	return 0;

error:
	iwl_remove_notification(&mvm->notif_wait, &init_wait);
	return ret;
}