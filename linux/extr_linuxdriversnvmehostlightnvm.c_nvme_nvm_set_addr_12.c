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
struct nvme_nvm_id12_addrf {unsigned long long ch_len; unsigned long long lun_len; unsigned long long blk_len; unsigned long long pg_len; unsigned long long pln_len; unsigned long long sec_len; unsigned long long ch_offset; unsigned long long lun_offset; unsigned long long blk_offset; unsigned long long pg_offset; unsigned long long pln_offset; unsigned long long sec_offset; } ;
struct nvm_addrf_12 {unsigned long long ch_len; unsigned long long lun_len; unsigned long long blk_len; unsigned long long pg_len; unsigned long long pln_len; unsigned long long sec_len; unsigned long long ch_offset; unsigned long long lun_offset; unsigned long long blk_offset; unsigned long long pg_offset; unsigned long long pln_offset; unsigned long long sec_offset; unsigned long long ch_mask; unsigned long long lun_mask; unsigned long long blk_mask; unsigned long long pg_mask; unsigned long long pln_mask; unsigned long long sec_mask; } ;

/* Variables and functions */

__attribute__((used)) static void nvme_nvm_set_addr_12(struct nvm_addrf_12 *dst,
				 struct nvme_nvm_id12_addrf *src)
{
	dst->ch_len = src->ch_len;
	dst->lun_len = src->lun_len;
	dst->blk_len = src->blk_len;
	dst->pg_len = src->pg_len;
	dst->pln_len = src->pln_len;
	dst->sec_len = src->sec_len;

	dst->ch_offset = src->ch_offset;
	dst->lun_offset = src->lun_offset;
	dst->blk_offset = src->blk_offset;
	dst->pg_offset = src->pg_offset;
	dst->pln_offset = src->pln_offset;
	dst->sec_offset = src->sec_offset;

	dst->ch_mask = ((1ULL << dst->ch_len) - 1) << dst->ch_offset;
	dst->lun_mask = ((1ULL << dst->lun_len) - 1) << dst->lun_offset;
	dst->blk_mask = ((1ULL << dst->blk_len) - 1) << dst->blk_offset;
	dst->pg_mask = ((1ULL << dst->pg_len) - 1) << dst->pg_offset;
	dst->pln_mask = ((1ULL << dst->pln_len) - 1) << dst->pln_offset;
	dst->sec_mask = ((1ULL << dst->sec_len) - 1) << dst->sec_offset;
}