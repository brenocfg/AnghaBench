#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
typedef  scalar_t__ u32 ;
struct iwl_mvm {char const* nvm_file_name; TYPE_5__* nvm_data; TYPE_3__* trans; TYPE_4__* nvm_sections; TYPE_2__* cfg; } ;
struct TYPE_10__ {int /*<<< orphan*/  nvm_version; } ;
struct TYPE_9__ {int length; int /*<<< orphan*/ * data; } ;
struct TYPE_8__ {int /*<<< orphan*/  dev; int /*<<< orphan*/  hw_id; } ;
struct TYPE_7__ {char* default_nvm_file_C_step; int nvm_hw_section_num; TYPE_1__* base_params; } ;
struct TYPE_6__ {int /*<<< orphan*/  eeprom_size; } ;

/* Variables and functions */
 int EFAULT ; 
 int EINVAL ; 
 int ENODATA ; 
 int ENOENT ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IWL_DEBUG_EEPROM (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  IWL_ERR (struct iwl_mvm*,char*) ; 
 int NVM_MAX_NUM_SECTIONS ; 
 scalar_t__ WARN_ON_ONCE (int) ; 
 int /*<<< orphan*/  iwl_nvm_fixups (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int) ; 
 int iwl_nvm_read_section (struct iwl_mvm*,int,int /*<<< orphan*/ *,scalar_t__) ; 
 TYPE_5__* iwl_parse_nvm_sections (struct iwl_mvm*) ; 
 int iwl_read_external_nvm (TYPE_3__*,char const*,TYPE_4__*) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * kmalloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * kmemdup (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 

int iwl_nvm_init(struct iwl_mvm *mvm)
{
	int ret, section;
	u32 size_read = 0;
	u8 *nvm_buffer, *temp;
	const char *nvm_file_C = mvm->cfg->default_nvm_file_C_step;

	if (WARN_ON_ONCE(mvm->cfg->nvm_hw_section_num >= NVM_MAX_NUM_SECTIONS))
		return -EINVAL;

	/* load NVM values from nic */
	/* Read From FW NVM */
	IWL_DEBUG_EEPROM(mvm->trans->dev, "Read from NVM\n");

	nvm_buffer = kmalloc(mvm->cfg->base_params->eeprom_size,
			     GFP_KERNEL);
	if (!nvm_buffer)
		return -ENOMEM;
	for (section = 0; section < NVM_MAX_NUM_SECTIONS; section++) {
		/* we override the constness for initial read */
		ret = iwl_nvm_read_section(mvm, section, nvm_buffer,
					   size_read);
		if (ret < 0)
			continue;
		size_read += ret;
		temp = kmemdup(nvm_buffer, ret, GFP_KERNEL);
		if (!temp) {
			ret = -ENOMEM;
			break;
		}

		iwl_nvm_fixups(mvm->trans->hw_id, section, temp, ret);

		mvm->nvm_sections[section].data = temp;
		mvm->nvm_sections[section].length = ret;

#ifdef CONFIG_IWLWIFI_DEBUGFS
		switch (section) {
		case NVM_SECTION_TYPE_SW:
			mvm->nvm_sw_blob.data = temp;
			mvm->nvm_sw_blob.size  = ret;
			break;
		case NVM_SECTION_TYPE_CALIBRATION:
			mvm->nvm_calib_blob.data = temp;
			mvm->nvm_calib_blob.size  = ret;
			break;
		case NVM_SECTION_TYPE_PRODUCTION:
			mvm->nvm_prod_blob.data = temp;
			mvm->nvm_prod_blob.size  = ret;
			break;
		case NVM_SECTION_TYPE_PHY_SKU:
			mvm->nvm_phy_sku_blob.data = temp;
			mvm->nvm_phy_sku_blob.size  = ret;
			break;
		default:
			if (section == mvm->cfg->nvm_hw_section_num) {
				mvm->nvm_hw_blob.data = temp;
				mvm->nvm_hw_blob.size = ret;
				break;
			}
		}
#endif
	}
	if (!size_read)
		IWL_ERR(mvm, "OTP is blank\n");
	kfree(nvm_buffer);

	/* Only if PNVM selected in the mod param - load external NVM  */
	if (mvm->nvm_file_name) {
		/* read External NVM file from the mod param */
		ret = iwl_read_external_nvm(mvm->trans, mvm->nvm_file_name,
					    mvm->nvm_sections);
		if (ret) {
			mvm->nvm_file_name = nvm_file_C;

			if ((ret == -EFAULT || ret == -ENOENT) &&
			    mvm->nvm_file_name) {
				/* in case nvm file was failed try again */
				ret = iwl_read_external_nvm(mvm->trans,
							    mvm->nvm_file_name,
							    mvm->nvm_sections);
				if (ret)
					return ret;
			} else {
				return ret;
			}
		}
	}

	/* parse the relevant nvm sections */
	mvm->nvm_data = iwl_parse_nvm_sections(mvm);
	if (!mvm->nvm_data)
		return -ENODATA;
	IWL_DEBUG_EEPROM(mvm->trans->dev, "nvm version = %x\n",
			 mvm->nvm_data->nvm_version);

	return 0;
}