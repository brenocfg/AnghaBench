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
struct sst_fw {scalar_t__ size; scalar_t__ dma_buf; struct sst_dsp* dsp; } ;
struct sst_dsp {int /*<<< orphan*/  dev; } ;
struct sst_byt_fw_module_header {int mod_size; } ;
struct fw_header {scalar_t__ file_size; int modules; int /*<<< orphan*/  file_format; int /*<<< orphan*/  signature; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  SST_BYT_FW_SIGN ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,scalar_t__,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,...) ; 
 int sst_byt_parse_module (struct sst_dsp*,struct sst_fw*,struct sst_byt_fw_module_header*) ; 
 scalar_t__ strncmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int sst_byt_parse_fw_image(struct sst_fw *sst_fw)
{
	struct fw_header *header;
	struct sst_byt_fw_module_header *module;
	struct sst_dsp *dsp = sst_fw->dsp;
	int ret, count;

	/* Read the header information from the data pointer */
	header = (struct fw_header *)sst_fw->dma_buf;

	/* verify FW */
	if ((strncmp(header->signature, SST_BYT_FW_SIGN, 4) != 0) ||
	    (sst_fw->size != header->file_size + sizeof(*header))) {
		/* Invalid FW signature */
		dev_err(dsp->dev, "Invalid FW sign/filesize mismatch\n");
		return -EINVAL;
	}

	dev_dbg(dsp->dev,
		"header sign=%4s size=0x%x modules=0x%x fmt=0x%x size=%zu\n",
		header->signature, header->file_size, header->modules,
		header->file_format, sizeof(*header));

	module = (void *)sst_fw->dma_buf + sizeof(*header);
	for (count = 0; count < header->modules; count++) {
		/* module */
		ret = sst_byt_parse_module(dsp, sst_fw, module);
		if (ret < 0) {
			dev_err(dsp->dev, "invalid module %d\n", count);
			return ret;
		}
		module = (void *)module + sizeof(*module) + module->mod_size;
	}

	return 0;
}