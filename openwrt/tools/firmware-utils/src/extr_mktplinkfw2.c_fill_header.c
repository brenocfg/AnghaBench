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
struct fw_header {int kernel_la; int kernel_ep; int unk5; scalar_t__* md5sum1; int /*<<< orphan*/  ver_lo; int /*<<< orphan*/  ver_mid; int /*<<< orphan*/  ver_hi; int /*<<< orphan*/  sver_lo; int /*<<< orphan*/  sver_hi; int /*<<< orphan*/  unk4; void* unk3; void* unk2; void* boot_len; void* boot_ofs; void* rootfs_len; void* rootfs_ofs; void* kernel_len; void* kernel_ofs; void* fw_length; void* hw_ver_add; void* hw_rev; void* hw_id; scalar_t__* fw_version; void* version; } ;
struct TYPE_8__ {int hw_id; int hw_rev; int hw_ver_add; int flags; } ;
struct TYPE_7__ {int file_size; } ;
struct TYPE_6__ {int fw_max_len; } ;
struct TYPE_5__ {int file_size; } ;

/* Variables and functions */
 int FLAG_LE_KERNEL_LA_EP ; 
 TYPE_4__* board ; 
 TYPE_3__ boot_info ; 
 int bswap_32 (int) ; 
 int /*<<< orphan*/  combined ; 
 int /*<<< orphan*/  fw_ver_hi ; 
 int /*<<< orphan*/  fw_ver_lo ; 
 int /*<<< orphan*/  fw_ver_mid ; 
 int /*<<< orphan*/  get_md5 (char*,int,scalar_t__*) ; 
 int hdr_ver ; 
 void* htonl (int) ; 
 int /*<<< orphan*/  htons (int) ; 
 int kernel_ep ; 
 int kernel_la ; 
 int kernel_len ; 
 TYPE_2__* layout ; 
 int /*<<< orphan*/  md5salt_boot ; 
 int /*<<< orphan*/  md5salt_normal ; 
 int /*<<< orphan*/  memcpy (scalar_t__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  memset (struct fw_header*,float,int) ; 
 TYPE_1__ rootfs_info ; 
 int rootfs_ofs ; 
 unsigned int strlen (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sver_hi ; 
 int /*<<< orphan*/  sver_lo ; 
 int /*<<< orphan*/  version ; 

void fill_header(char *buf, int len)
{
	struct fw_header *hdr = (struct fw_header *)buf;
	unsigned ver_len;

	memset(hdr, '\xff', sizeof(struct fw_header));

	hdr->version = htonl(bswap_32(hdr_ver));
	ver_len = strlen(version);
	if (ver_len > (sizeof(hdr->fw_version) - 1))
		ver_len = sizeof(hdr->fw_version) - 1;

	memcpy(hdr->fw_version, version, ver_len);
	hdr->fw_version[ver_len] = 0;

	hdr->hw_id = htonl(board->hw_id);
	hdr->hw_rev = htonl(board->hw_rev);
	hdr->hw_ver_add = htonl(board->hw_ver_add);

	if (boot_info.file_size == 0) {
		memcpy(hdr->md5sum1, md5salt_normal, sizeof(hdr->md5sum1));
		hdr->boot_ofs = htonl(0);
		hdr->boot_len = htonl(0);
	} else {
		memcpy(hdr->md5sum1, md5salt_boot, sizeof(hdr->md5sum1));
		hdr->boot_ofs = htonl(rootfs_ofs + rootfs_info.file_size);
		hdr->boot_len = htonl(rootfs_info.file_size);
	}

	hdr->kernel_la = htonl(kernel_la);
	hdr->kernel_ep = htonl(kernel_ep);
	hdr->fw_length = htonl(layout->fw_max_len);
	hdr->kernel_ofs = htonl(sizeof(struct fw_header));
	hdr->kernel_len = htonl(kernel_len);
	if (!combined) {
		hdr->rootfs_ofs = htonl(rootfs_ofs);
		hdr->rootfs_len = htonl(rootfs_info.file_size);
	}

	hdr->boot_ofs = htonl(0);
	hdr->boot_len = htonl(boot_info.file_size);

	hdr->unk2 = htonl(0);
	hdr->unk3 = htonl(0xffffffff);
	hdr->unk4 = htons(0x55aa);
	hdr->unk5 = 0xa5;

	hdr->sver_hi = sver_hi;
	hdr->sver_lo = sver_lo;

	hdr->ver_hi = fw_ver_hi;
	hdr->ver_mid = fw_ver_mid;
	hdr->ver_lo = fw_ver_lo;

	if (board->flags & FLAG_LE_KERNEL_LA_EP) {
		hdr->kernel_la = bswap_32(hdr->kernel_la);
		hdr->kernel_ep = bswap_32(hdr->kernel_ep);
	}

	get_md5(buf, len, hdr->md5sum1);
}