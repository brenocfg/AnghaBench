#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct fw_header {int /*<<< orphan*/  md5sum1; void* kernel_ep; void* kernel_la; int /*<<< orphan*/  region_str2; int /*<<< orphan*/  region_str1; void* region_code; void* ver_lo; void* ver_mid; void* ver_hi; void* rootfs_ofs; void* rootfs_len; void* fw_length; void* kernel_len; void* kernel_ofs; void* hw_rev; void* hw_id; int /*<<< orphan*/  fw_version; int /*<<< orphan*/  vendor_name; void* version; } ;
struct TYPE_8__ {scalar_t__ file_size; } ;
struct TYPE_7__ {int fw_max_len; } ;
struct TYPE_6__ {int code; int* name; } ;
struct TYPE_5__ {int file_size; } ;

/* Variables and functions */
 TYPE_4__ boot_info ; 
 void* bswap_32 (void*) ; 
 scalar_t__ combined ; 
 scalar_t__ endian_swap ; 
 int /*<<< orphan*/  fw_ver_hi ; 
 int /*<<< orphan*/  fw_ver_lo ; 
 int /*<<< orphan*/  fw_ver_mid ; 
 int /*<<< orphan*/  get_md5 (char*,int,int /*<<< orphan*/ ) ; 
 int hdr_ver ; 
 void* htonl (int) ; 
 void* htons (int /*<<< orphan*/ ) ; 
 int hw_id ; 
 int hw_rev ; 
 int kernel_ep ; 
 int kernel_la ; 
 int kernel_len ; 
 TYPE_3__* layout ; 
 int /*<<< orphan*/  md5salt_boot ; 
 int /*<<< orphan*/  md5salt_normal ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  memset (struct fw_header*,int /*<<< orphan*/ ,int) ; 
 TYPE_2__* region ; 
 TYPE_1__ rootfs_info ; 
 int rootfs_ofs ; 
 scalar_t__ rootfs_ofs_calc ; 
 int /*<<< orphan*/  snprintf (int /*<<< orphan*/ ,int,char*,int,int,int,int) ; 
 int /*<<< orphan*/  strncpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  vendor ; 
 int /*<<< orphan*/  version ; 

void fill_header(char *buf, int len)
{
	struct fw_header *hdr = (struct fw_header *)buf;

	memset(hdr, 0, sizeof(struct fw_header));

	hdr->version = htonl(hdr_ver);
	strncpy(hdr->vendor_name, vendor, sizeof(hdr->vendor_name));
	strncpy(hdr->fw_version, version, sizeof(hdr->fw_version));
	hdr->hw_id = htonl(hw_id);
	hdr->hw_rev = htonl(hw_rev);

	hdr->kernel_la = htonl(kernel_la);
	hdr->kernel_ep = htonl(kernel_ep);
	hdr->kernel_ofs = htonl(sizeof(struct fw_header));
	hdr->kernel_len = htonl(kernel_len);

	if (!combined) {
		if (boot_info.file_size == 0)
			memcpy(hdr->md5sum1, md5salt_normal, sizeof(hdr->md5sum1));
		else
			memcpy(hdr->md5sum1, md5salt_boot, sizeof(hdr->md5sum1));

		hdr->fw_length = htonl(layout->fw_max_len);
		hdr->rootfs_ofs = htonl(rootfs_ofs);
		hdr->rootfs_len = htonl(rootfs_info.file_size);
	}

	if (combined && rootfs_ofs_calc) {
		hdr->rootfs_ofs = htonl(sizeof(struct fw_header) + kernel_len);
	}

	hdr->ver_hi = htons(fw_ver_hi);
	hdr->ver_mid = htons(fw_ver_mid);
	hdr->ver_lo = htons(fw_ver_lo);

	if (region) {
		hdr->region_code = htonl(region->code);
		snprintf(
			hdr->region_str1, sizeof(hdr->region_str1), "00000000;%02X%02X%02X%02X;",
			region->name[0], region->name[1], region->name[2], region->name[3]
		);
		snprintf(
			hdr->region_str2, sizeof(hdr->region_str2), "%02X%02X%02X%02X",
			region->name[0], region->name[1], region->name[2], region->name[3]
		);
	}

	if (endian_swap) {
		hdr->kernel_la = bswap_32(hdr->kernel_la);
		hdr->kernel_ep = bswap_32(hdr->kernel_ep);
	}

	if (!combined)
		get_md5(buf, len, hdr->md5sum1);
}