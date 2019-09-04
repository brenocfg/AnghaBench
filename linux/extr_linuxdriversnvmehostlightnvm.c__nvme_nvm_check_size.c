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
struct nvme_nvm_setbbtbl {int dummy; } ;
struct nvme_nvm_ph_rw {int dummy; } ;
struct nvme_nvm_identity {int dummy; } ;
struct nvme_nvm_id20_addrf {int dummy; } ;
struct nvme_nvm_id20 {int dummy; } ;
struct nvme_nvm_id12_grp {int dummy; } ;
struct nvme_nvm_id12_addrf {int dummy; } ;
struct nvme_nvm_id12 {int dummy; } ;
struct nvme_nvm_getbbtbl {int dummy; } ;
struct nvme_nvm_erase_blk {int dummy; } ;
struct nvme_nvm_chk_meta {int dummy; } ;
struct nvme_nvm_bb_tbl {int dummy; } ;
struct nvm_chk_meta {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUILD_BUG_ON (int) ; 
 int NVME_IDENTIFY_DATA_SIZE ; 

__attribute__((used)) static inline void _nvme_nvm_check_size(void)
{
	BUILD_BUG_ON(sizeof(struct nvme_nvm_identity) != 64);
	BUILD_BUG_ON(sizeof(struct nvme_nvm_ph_rw) != 64);
	BUILD_BUG_ON(sizeof(struct nvme_nvm_erase_blk) != 64);
	BUILD_BUG_ON(sizeof(struct nvme_nvm_getbbtbl) != 64);
	BUILD_BUG_ON(sizeof(struct nvme_nvm_setbbtbl) != 64);
	BUILD_BUG_ON(sizeof(struct nvme_nvm_id12_grp) != 960);
	BUILD_BUG_ON(sizeof(struct nvme_nvm_id12_addrf) != 16);
	BUILD_BUG_ON(sizeof(struct nvme_nvm_id12) != NVME_IDENTIFY_DATA_SIZE);
	BUILD_BUG_ON(sizeof(struct nvme_nvm_bb_tbl) != 64);
	BUILD_BUG_ON(sizeof(struct nvme_nvm_id20_addrf) != 8);
	BUILD_BUG_ON(sizeof(struct nvme_nvm_id20) != NVME_IDENTIFY_DATA_SIZE);
	BUILD_BUG_ON(sizeof(struct nvme_nvm_chk_meta) != 32);
	BUILD_BUG_ON(sizeof(struct nvme_nvm_chk_meta) !=
						sizeof(struct nvm_chk_meta));
}