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
typedef  char u8 ;
struct ipr_ucode_image_header {int /*<<< orphan*/  header_length; } ;
struct ipr_sglist {int dummy; } ;
struct ipr_ioa_cfg {TYPE_1__* pdev; } ;
struct firmware {int size; scalar_t__ data; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
struct Scsi_Host {scalar_t__ hostdata; } ;
typedef  int ssize_t ;
typedef  int /*<<< orphan*/  fname ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  CAP_SYS_ADMIN ; 
 int EACCES ; 
 int EIO ; 
 int ENOMEM ; 
 int be32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  capable (int /*<<< orphan*/ ) ; 
 struct Scsi_Host* class_to_shost (struct device*) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,...) ; 
 struct ipr_sglist* ipr_alloc_ucode_buffer (int) ; 
 int ipr_copy_ucode_buffer (struct ipr_sglist*,char*,int) ; 
 int /*<<< orphan*/  ipr_free_ucode_buffer (struct ipr_sglist*) ; 
 int /*<<< orphan*/  ipr_info (char*) ; 
 int ipr_update_ioa_ucode (struct ipr_ioa_cfg*,struct ipr_sglist*) ; 
 int /*<<< orphan*/  release_firmware (struct firmware const*) ; 
 scalar_t__ request_firmware (struct firmware const**,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char const*) ; 
 char* strchr (char*,char) ; 

__attribute__((used)) static ssize_t ipr_store_update_fw(struct device *dev,
				   struct device_attribute *attr,
				   const char *buf, size_t count)
{
	struct Scsi_Host *shost = class_to_shost(dev);
	struct ipr_ioa_cfg *ioa_cfg = (struct ipr_ioa_cfg *)shost->hostdata;
	struct ipr_ucode_image_header *image_hdr;
	const struct firmware *fw_entry;
	struct ipr_sglist *sglist;
	char fname[100];
	char *src;
	char *endline;
	int result, dnld_size;

	if (!capable(CAP_SYS_ADMIN))
		return -EACCES;

	snprintf(fname, sizeof(fname), "%s", buf);

	endline = strchr(fname, '\n');
	if (endline)
		*endline = '\0';

	if (request_firmware(&fw_entry, fname, &ioa_cfg->pdev->dev)) {
		dev_err(&ioa_cfg->pdev->dev, "Firmware file %s not found\n", fname);
		return -EIO;
	}

	image_hdr = (struct ipr_ucode_image_header *)fw_entry->data;

	src = (u8 *)image_hdr + be32_to_cpu(image_hdr->header_length);
	dnld_size = fw_entry->size - be32_to_cpu(image_hdr->header_length);
	sglist = ipr_alloc_ucode_buffer(dnld_size);

	if (!sglist) {
		dev_err(&ioa_cfg->pdev->dev, "Microcode buffer allocation failed\n");
		release_firmware(fw_entry);
		return -ENOMEM;
	}

	result = ipr_copy_ucode_buffer(sglist, src, dnld_size);

	if (result) {
		dev_err(&ioa_cfg->pdev->dev,
			"Microcode buffer copy to DMA buffer failed\n");
		goto out;
	}

	ipr_info("Updating microcode, please be patient.  This may take up to 30 minutes.\n");

	result = ipr_update_ioa_ucode(ioa_cfg, sglist);

	if (!result)
		result = count;
out:
	ipr_free_ucode_buffer(sglist);
	release_firmware(fw_entry);
	return result;
}