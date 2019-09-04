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
struct nvme_nvm_id20_addrf {unsigned long long grp_len; unsigned long long pu_len; unsigned long long chk_len; unsigned long long lba_len; } ;
struct nvm_addrf {unsigned long long ch_len; unsigned long long lun_len; unsigned long long chk_len; unsigned long long sec_len; unsigned long long sec_offset; unsigned long long chk_offset; unsigned long long lun_offset; unsigned long long ch_offset; unsigned long long ch_mask; unsigned long long lun_mask; unsigned long long chk_mask; unsigned long long sec_mask; } ;

/* Variables and functions */

__attribute__((used)) static void nvme_nvm_set_addr_20(struct nvm_addrf *dst,
				 struct nvme_nvm_id20_addrf *src)
{
	dst->ch_len = src->grp_len;
	dst->lun_len = src->pu_len;
	dst->chk_len = src->chk_len;
	dst->sec_len = src->lba_len;

	dst->sec_offset = 0;
	dst->chk_offset = dst->sec_len;
	dst->lun_offset = dst->chk_offset + dst->chk_len;
	dst->ch_offset = dst->lun_offset + dst->lun_len;

	dst->ch_mask = ((1ULL << dst->ch_len) - 1) << dst->ch_offset;
	dst->lun_mask = ((1ULL << dst->lun_len) - 1) << dst->lun_offset;
	dst->chk_mask = ((1ULL << dst->chk_len) - 1) << dst->chk_offset;
	dst->sec_mask = ((1ULL << dst->sec_len) - 1) << dst->sec_offset;
}