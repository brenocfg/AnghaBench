#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_7__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct fw_header {int dummy; } ;
struct TYPE_11__ {int hw_rev; void* hw_ver_add; void* hw_id; } ;
struct TYPE_10__ {int rootfs_ofs; int fw_max_len; scalar_t__ kernel_ep; scalar_t__ kernel_la; } ;
struct TYPE_9__ {int file_size; int /*<<< orphan*/ * file_name; } ;

/* Variables and functions */
 int ALIGN (int,scalar_t__) ; 
 int /*<<< orphan*/  DBG (char*,int) ; 
 int /*<<< orphan*/  ERR (char*,...) ; 
 TYPE_7__* board ; 
 scalar_t__ combined ; 
 TYPE_7__ custom_board ; 
 scalar_t__ extract ; 
 TYPE_2__* find_layout (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fw_ver ; 
 int /*<<< orphan*/  fw_ver_hi ; 
 int /*<<< orphan*/  fw_ver_lo ; 
 int /*<<< orphan*/  fw_ver_mid ; 
 int get_file_stat (TYPE_1__*) ; 
 TYPE_1__ inspect_info ; 
 scalar_t__ kernel_ep ; 
 TYPE_1__ kernel_info ; 
 scalar_t__ kernel_la ; 
 int kernel_len ; 
 TYPE_2__* layout ; 
 int /*<<< orphan*/ * layout_id ; 
 int /*<<< orphan*/  layouts ; 
 int /*<<< orphan*/ * ofname ; 
 int /*<<< orphan*/ * opt_hw_id ; 
 int /*<<< orphan*/ * opt_hw_rev ; 
 int /*<<< orphan*/ * opt_hw_ver_add ; 
 scalar_t__ rootfs_align ; 
 TYPE_1__ rootfs_info ; 
 int rootfs_ofs ; 
 int sscanf (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,...) ; 
 void* strtoul (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * sver ; 
 int /*<<< orphan*/  sver_hi ; 
 int /*<<< orphan*/  sver_lo ; 

__attribute__((used)) static int check_options(void)
{
	int ret;

	if (inspect_info.file_name) {
		ret = get_file_stat(&inspect_info);
		if (ret)
			return ret;

		return 0;
	} else if (extract) {
		ERR("no firmware for inspection specified");
		return -1;
	}

	if (opt_hw_id == NULL) {
		ERR("hardware id must be specified");
		return -1;
	}

	board = &custom_board;

	if (layout_id == NULL) {
		ERR("flash layout is not specified");
		return -1;
	}

	board->hw_id = strtoul(opt_hw_id, NULL, 0);

	board->hw_rev = 1;
	board->hw_ver_add = 0;

	if (opt_hw_rev)
		board->hw_rev = strtoul(opt_hw_rev, NULL, 0);
	if (opt_hw_ver_add)
		board->hw_ver_add = strtoul(opt_hw_ver_add, NULL, 0);

	layout = find_layout(layouts, layout_id);
	if (layout == NULL) {
		ERR("unknown flash layout \"%s\"", layout_id);
		return -1;
	}

	if (!kernel_la)
		kernel_la = layout->kernel_la;
	if (!kernel_ep)
		kernel_ep = layout->kernel_ep;
	if (!rootfs_ofs)
		rootfs_ofs = layout->rootfs_ofs;

	if (kernel_info.file_name == NULL) {
		ERR("no kernel image specified");
		return -1;
	}

	ret = get_file_stat(&kernel_info);
	if (ret)
		return ret;

	kernel_len = kernel_info.file_size;

	if (combined) {
		if (kernel_info.file_size >
		    layout->fw_max_len - sizeof(struct fw_header)) {
			ERR("kernel image is too big");
			return -1;
		}
	} else {
		if (rootfs_info.file_name == NULL) {
			ERR("no rootfs image specified");
			return -1;
		}

		ret = get_file_stat(&rootfs_info);
		if (ret)
			return ret;

		if (rootfs_align) {
			kernel_len += sizeof(struct fw_header);
			rootfs_ofs = ALIGN(kernel_len, rootfs_align);
			kernel_len -= sizeof(struct fw_header);

			DBG("rootfs offset aligned to 0x%u", rootfs_ofs);

			if (kernel_len + rootfs_info.file_size >
			    layout->fw_max_len - sizeof(struct fw_header)) {
				ERR("images are too big");
				return -1;
			}
		} else {
			if (kernel_info.file_size >
			    rootfs_ofs - sizeof(struct fw_header)) {
				ERR("kernel image is too big");
				return -1;
			}

			if (rootfs_info.file_size >
			    (layout->fw_max_len - rootfs_ofs)) {
				ERR("rootfs image is too big");
				return -1;
			}
		}
	}

	if (ofname == NULL) {
		ERR("no output file specified");
		return -1;
	}

	ret = sscanf(fw_ver, "%d.%d.%d", &fw_ver_hi, &fw_ver_mid, &fw_ver_lo);
	if (ret != 3) {
		ERR("invalid firmware version '%s'", fw_ver);
		return -1;
	}

	ret = sscanf(sver, "%d.%d", &sver_hi, &sver_lo);
	if (ret != 2) {
		ERR("invalid secondary version '%s'", sver);
		return -1;
	}

	return 0;
}