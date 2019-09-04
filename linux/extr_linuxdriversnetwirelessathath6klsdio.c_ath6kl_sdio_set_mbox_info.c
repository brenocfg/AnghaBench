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
struct ath6kl_mbox_info {int /*<<< orphan*/  gmbox_sz; int /*<<< orphan*/  gmbox_addr; int /*<<< orphan*/  block_size; int /*<<< orphan*/  htc_ext_sz; int /*<<< orphan*/  htc_ext_addr; int /*<<< orphan*/  htc_addr; } ;
struct ath6kl {struct ath6kl_mbox_info mbox_info; } ;

/* Variables and functions */
 int /*<<< orphan*/  HIF_GMBOX_BASE_ADDR ; 
 int /*<<< orphan*/  HIF_GMBOX_WIDTH ; 
 int /*<<< orphan*/  HIF_MBOX0_EXT_BASE_ADDR ; 
 int /*<<< orphan*/  HIF_MBOX0_EXT_WIDTH ; 
 int /*<<< orphan*/  HIF_MBOX_BASE_ADDR ; 
 int /*<<< orphan*/  HIF_MBOX_BLOCK_SIZE ; 

__attribute__((used)) static void ath6kl_sdio_set_mbox_info(struct ath6kl *ar)
{
	struct ath6kl_mbox_info *mbox_info = &ar->mbox_info;

	/* EP1 has an extended range */
	mbox_info->htc_addr = HIF_MBOX_BASE_ADDR;
	mbox_info->htc_ext_addr = HIF_MBOX0_EXT_BASE_ADDR;
	mbox_info->htc_ext_sz = HIF_MBOX0_EXT_WIDTH;
	mbox_info->block_size = HIF_MBOX_BLOCK_SIZE;
	mbox_info->gmbox_addr = HIF_GMBOX_BASE_ADDR;
	mbox_info->gmbox_sz = HIF_GMBOX_WIDTH;
}