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
typedef  int /*<<< orphan*/  const u8 ;
typedef  int /*<<< orphan*/  u32 ;
typedef  size_t u16 ;
struct iwl_trans {int /*<<< orphan*/  hw_id; TYPE_1__* cfg; int /*<<< orphan*/  hw_rev; int /*<<< orphan*/  dev; } ;
struct iwl_nvm_section {int length; int /*<<< orphan*/  const* data; } ;
struct firmware {int size; int /*<<< orphan*/  const* data; } ;
typedef  scalar_t__ __le32 ;
typedef  int /*<<< orphan*/  __le16 ;
struct TYPE_2__ {scalar_t__ nvm_type; scalar_t__ device_family; } ;

/* Variables and functions */
 scalar_t__ CSR_HW_REV_STEP (int /*<<< orphan*/ ) ; 
 int EFAULT ; 
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IWL_DEBUG_EEPROM (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ IWL_DEVICE_FAMILY_8000 ; 
 int /*<<< orphan*/  IWL_ERR (struct iwl_trans*,char*,...) ; 
 int /*<<< orphan*/  IWL_INFO (struct iwl_trans*,char*,...) ; 
 int IWL_MAX_EXT_NVM_SECTION_SIZE ; 
 int IWL_MAX_NVM_SECTION_SIZE ; 
 scalar_t__ IWL_NVM_EXT ; 
 int MAX_NVM_FILE_LEN ; 
 size_t NVM_MAX_NUM_SECTIONS ; 
 scalar_t__ SILICON_C_STEP ; 
 scalar_t__ WARN (int,char*,size_t) ; 
 scalar_t__ const cpu_to_le32 (int) ; 
 int /*<<< orphan*/  iwl_nvm_fixups (int /*<<< orphan*/ ,size_t,int /*<<< orphan*/  const*,int) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  const* kmemdup (int /*<<< orphan*/  const*,int,int /*<<< orphan*/ ) ; 
 int le16_to_cpu (int /*<<< orphan*/ ) ; 
 int le32_to_cpu (scalar_t__ const) ; 
 int /*<<< orphan*/  release_firmware (struct firmware const*) ; 
 int request_firmware (struct firmware const**,char const*,int /*<<< orphan*/ ) ; 

int iwl_read_external_nvm(struct iwl_trans *trans,
			  const char *nvm_file_name,
			  struct iwl_nvm_section *nvm_sections)
{
	int ret, section_size;
	u16 section_id;
	const struct firmware *fw_entry;
	const struct {
		__le16 word1;
		__le16 word2;
		u8 data[];
	} *file_sec;
	const u8 *eof;
	u8 *temp;
	int max_section_size;
	const __le32 *dword_buff;

#define NVM_WORD1_LEN(x) (8 * (x & 0x03FF))
#define NVM_WORD2_ID(x) (x >> 12)
#define EXT_NVM_WORD2_LEN(x) (2 * (((x) & 0xFF) << 8 | (x) >> 8))
#define EXT_NVM_WORD1_ID(x) ((x) >> 4)
#define NVM_HEADER_0	(0x2A504C54)
#define NVM_HEADER_1	(0x4E564D2A)
#define NVM_HEADER_SIZE	(4 * sizeof(u32))

	IWL_DEBUG_EEPROM(trans->dev, "Read from external NVM\n");

	/* Maximal size depends on NVM version */
	if (trans->cfg->nvm_type != IWL_NVM_EXT)
		max_section_size = IWL_MAX_NVM_SECTION_SIZE;
	else
		max_section_size = IWL_MAX_EXT_NVM_SECTION_SIZE;

	/*
	 * Obtain NVM image via request_firmware. Since we already used
	 * request_firmware_nowait() for the firmware binary load and only
	 * get here after that we assume the NVM request can be satisfied
	 * synchronously.
	 */
	ret = request_firmware(&fw_entry, nvm_file_name, trans->dev);
	if (ret) {
		IWL_ERR(trans, "ERROR: %s isn't available %d\n",
			nvm_file_name, ret);
		return ret;
	}

	IWL_INFO(trans, "Loaded NVM file %s (%zu bytes)\n",
		 nvm_file_name, fw_entry->size);

	if (fw_entry->size > MAX_NVM_FILE_LEN) {
		IWL_ERR(trans, "NVM file too large\n");
		ret = -EINVAL;
		goto out;
	}

	eof = fw_entry->data + fw_entry->size;
	dword_buff = (__le32 *)fw_entry->data;

	/* some NVM file will contain a header.
	 * The header is identified by 2 dwords header as follow:
	 * dword[0] = 0x2A504C54
	 * dword[1] = 0x4E564D2A
	 *
	 * This header must be skipped when providing the NVM data to the FW.
	 */
	if (fw_entry->size > NVM_HEADER_SIZE &&
	    dword_buff[0] == cpu_to_le32(NVM_HEADER_0) &&
	    dword_buff[1] == cpu_to_le32(NVM_HEADER_1)) {
		file_sec = (void *)(fw_entry->data + NVM_HEADER_SIZE);
		IWL_INFO(trans, "NVM Version %08X\n", le32_to_cpu(dword_buff[2]));
		IWL_INFO(trans, "NVM Manufacturing date %08X\n",
			 le32_to_cpu(dword_buff[3]));

		/* nvm file validation, dword_buff[2] holds the file version */
		if (trans->cfg->device_family == IWL_DEVICE_FAMILY_8000 &&
		    CSR_HW_REV_STEP(trans->hw_rev) == SILICON_C_STEP &&
		    le32_to_cpu(dword_buff[2]) < 0xE4A) {
			ret = -EFAULT;
			goto out;
		}
	} else {
		file_sec = (void *)fw_entry->data;
	}

	while (true) {
		if (file_sec->data > eof) {
			IWL_ERR(trans,
				"ERROR - NVM file too short for section header\n");
			ret = -EINVAL;
			break;
		}

		/* check for EOF marker */
		if (!file_sec->word1 && !file_sec->word2) {
			ret = 0;
			break;
		}

		if (trans->cfg->nvm_type != IWL_NVM_EXT) {
			section_size =
				2 * NVM_WORD1_LEN(le16_to_cpu(file_sec->word1));
			section_id = NVM_WORD2_ID(le16_to_cpu(file_sec->word2));
		} else {
			section_size = 2 * EXT_NVM_WORD2_LEN(
						le16_to_cpu(file_sec->word2));
			section_id = EXT_NVM_WORD1_ID(
						le16_to_cpu(file_sec->word1));
		}

		if (section_size > max_section_size) {
			IWL_ERR(trans, "ERROR - section too large (%d)\n",
				section_size);
			ret = -EINVAL;
			break;
		}

		if (!section_size) {
			IWL_ERR(trans, "ERROR - section empty\n");
			ret = -EINVAL;
			break;
		}

		if (file_sec->data + section_size > eof) {
			IWL_ERR(trans,
				"ERROR - NVM file too short for section (%d bytes)\n",
				section_size);
			ret = -EINVAL;
			break;
		}

		if (WARN(section_id >= NVM_MAX_NUM_SECTIONS,
			 "Invalid NVM section ID %d\n", section_id)) {
			ret = -EINVAL;
			break;
		}

		temp = kmemdup(file_sec->data, section_size, GFP_KERNEL);
		if (!temp) {
			ret = -ENOMEM;
			break;
		}

		iwl_nvm_fixups(trans->hw_id, section_id, temp, section_size);

		kfree(nvm_sections[section_id].data);
		nvm_sections[section_id].data = temp;
		nvm_sections[section_id].length = section_size;

		/* advance to the next section */
		file_sec = (void *)(file_sec->data + section_size);
	}
out:
	release_firmware(fw_entry);
	return ret;
}