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
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int /*<<< orphan*/  u32 ;
struct device {int dummy; } ;
struct pci_dev {int device; struct device dev; } ;
struct firmware {int size; scalar_t__ data; } ;
struct csio_hw {struct pci_dev* pdev; } ;

/* Variables and functions */
 int CSIO_HW_CHIP_MASK ; 
 int EINVAL ; 
 int ENOENT ; 
 int ENOMEM ; 
 char* FW_CFG_NAME_T5 ; 
 char* FW_CFG_NAME_T6 ; 
 unsigned int FW_PARAMS_PARAM_Y_G (int /*<<< orphan*/ ) ; 
 int FW_PARAMS_PARAM_Z_G (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  csio_err (struct csio_hw*,char*,char const*,int) ; 
 scalar_t__ csio_hw_check_fwconfig (struct csio_hw*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  csio_info (struct csio_hw*,char*,char const*) ; 
 scalar_t__ csio_is_t5 (int) ; 
 int csio_memory_write (struct csio_hw*,unsigned int,unsigned int,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (void*,void const*,int) ; 
 int /*<<< orphan*/  release_firmware (struct firmware const*) ; 
 scalar_t__ request_firmware (struct firmware const**,char const*,struct device*) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char*,char const*) ; 

__attribute__((used)) static int
csio_hw_flash_config(struct csio_hw *hw, u32 *fw_cfg_param, char *path)
{
	int ret = 0;
	const struct firmware *cf;
	struct pci_dev *pci_dev = hw->pdev;
	struct device *dev = &pci_dev->dev;
	unsigned int mtype = 0, maddr = 0;
	uint32_t *cfg_data;
	int value_to_add = 0;
	const char *fw_cfg_file;

	if (csio_is_t5(pci_dev->device & CSIO_HW_CHIP_MASK))
		fw_cfg_file = FW_CFG_NAME_T5;
	else
		fw_cfg_file = FW_CFG_NAME_T6;

	if (request_firmware(&cf, fw_cfg_file, dev) < 0) {
		csio_err(hw, "could not find config file %s, err: %d\n",
			 fw_cfg_file, ret);
		return -ENOENT;
	}

	if (cf->size%4 != 0)
		value_to_add = 4 - (cf->size % 4);

	cfg_data = kzalloc(cf->size+value_to_add, GFP_KERNEL);
	if (cfg_data == NULL) {
		ret = -ENOMEM;
		goto leave;
	}

	memcpy((void *)cfg_data, (const void *)cf->data, cf->size);
	if (csio_hw_check_fwconfig(hw, fw_cfg_param) != 0) {
		ret = -EINVAL;
		goto leave;
	}

	mtype = FW_PARAMS_PARAM_Y_G(*fw_cfg_param);
	maddr = FW_PARAMS_PARAM_Z_G(*fw_cfg_param) << 16;

	ret = csio_memory_write(hw, mtype, maddr,
				cf->size + value_to_add, cfg_data);

	if ((ret == 0) && (value_to_add != 0)) {
		union {
			u32 word;
			char buf[4];
		} last;
		size_t size = cf->size & ~0x3;
		int i;

		last.word = cfg_data[size >> 2];
		for (i = value_to_add; i < 4; i++)
			last.buf[i] = 0;
		ret = csio_memory_write(hw, mtype, maddr + size, 4, &last.word);
	}
	if (ret == 0) {
		csio_info(hw, "config file upgraded to %s\n", fw_cfg_file);
		snprintf(path, 64, "%s%s", "/lib/firmware/", fw_cfg_file);
	}

leave:
	kfree(cfg_data);
	release_firmware(cf);
	return ret;
}