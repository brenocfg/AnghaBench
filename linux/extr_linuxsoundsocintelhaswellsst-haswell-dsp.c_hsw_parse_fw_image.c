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
struct sst_fw {int size; scalar_t__ dma_buf; struct sst_dsp* dsp; } ;
struct sst_dsp {int /*<<< orphan*/  dev; } ;
struct fw_module_header {int /*<<< orphan*/  mod_size; } ;
struct fw_header {int /*<<< orphan*/  modules; int /*<<< orphan*/  file_format; int /*<<< orphan*/  file_size; int /*<<< orphan*/  signature; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  SST_HSW_FW_SIGN ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,...) ; 
 int hsw_parse_module (struct sst_dsp*,struct sst_fw*,struct fw_module_header*) ; 
 int le32_to_cpu (int /*<<< orphan*/ ) ; 
 scalar_t__ strncmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int hsw_parse_fw_image(struct sst_fw *sst_fw)
{
	struct fw_header *header;
	struct fw_module_header *module;
	struct sst_dsp *dsp = sst_fw->dsp;
	int ret, count;

	/* Read the header information from the data pointer */
	header = (struct fw_header *)sst_fw->dma_buf;

	/* verify FW */
	if ((strncmp(header->signature, SST_HSW_FW_SIGN, 4) != 0) ||
	    (sst_fw->size !=
	     le32_to_cpu(header->file_size) + sizeof(*header))) {
		dev_err(dsp->dev, "error: invalid fw sign/filesize mismatch\n");
		return -EINVAL;
	}

	dev_dbg(dsp->dev, "header size=0x%x modules=0x%x fmt=0x%x size=%zu\n",
		header->file_size, header->modules,
		header->file_format, sizeof(*header));

	/* parse each module */
	module = (void *)sst_fw->dma_buf + sizeof(*header);
	for (count = 0; count < le32_to_cpu(header->modules); count++) {

		/* module */
		ret = hsw_parse_module(dsp, sst_fw, module);
		if (ret < 0) {
			dev_err(dsp->dev, "error: invalid module %d\n", count);
			return ret;
		}
		module = (void *)module + sizeof(*module) +
			le32_to_cpu(module->mod_size);
	}

	return 0;
}