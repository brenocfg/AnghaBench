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
typedef  int u32 ;
struct iwl_trans {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  CSR_EEPROM_GP ; 
#define  CSR_EEPROM_GP_BAD_SIGNATURE_BOTH_EEP_AND_OTP 131 
#define  CSR_EEPROM_GP_BAD_SIG_EEP_GOOD_SIG_OTP 130 
#define  CSR_EEPROM_GP_GOOD_SIG_EEP_LESS_THAN_4K 129 
#define  CSR_EEPROM_GP_GOOD_SIG_EEP_MORE_THAN_4K 128 
 int CSR_EEPROM_GP_VALID_MSK ; 
 int ENOENT ; 
 int /*<<< orphan*/  IWL_DEBUG_EEPROM (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  IWL_ERR (struct iwl_trans*,char*,...) ; 
 int iwl_read32 (struct iwl_trans*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int iwl_eeprom_verify_signature(struct iwl_trans *trans, bool nvm_is_otp)
{
	u32 gp = iwl_read32(trans, CSR_EEPROM_GP) & CSR_EEPROM_GP_VALID_MSK;

	IWL_DEBUG_EEPROM(trans->dev, "EEPROM signature=0x%08x\n", gp);

	switch (gp) {
	case CSR_EEPROM_GP_BAD_SIG_EEP_GOOD_SIG_OTP:
		if (!nvm_is_otp) {
			IWL_ERR(trans, "EEPROM with bad signature: 0x%08x\n",
				gp);
			return -ENOENT;
		}
		return 0;
	case CSR_EEPROM_GP_GOOD_SIG_EEP_LESS_THAN_4K:
	case CSR_EEPROM_GP_GOOD_SIG_EEP_MORE_THAN_4K:
		if (nvm_is_otp) {
			IWL_ERR(trans, "OTP with bad signature: 0x%08x\n", gp);
			return -ENOENT;
		}
		return 0;
	case CSR_EEPROM_GP_BAD_SIGNATURE_BOTH_EEP_AND_OTP:
	default:
		IWL_ERR(trans,
			"bad EEPROM/OTP signature, type=%s, EEPROM_GP=0x%08x\n",
			nvm_is_otp ? "OTP" : "EEPROM", gp);
		return -ENOENT;
	}
}