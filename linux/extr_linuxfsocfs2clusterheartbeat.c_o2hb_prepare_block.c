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
typedef  int u64 ;
struct o2hb_region {int /*<<< orphan*/  hr_block_bytes; struct o2hb_disk_slot* hr_slots; } ;
struct o2hb_disk_slot {scalar_t__ ds_raw_block; } ;
struct o2hb_disk_heartbeat_block {int hb_node; void* hb_cksum; void* hb_dead_ms; void* hb_generation; void* hb_seq; } ;

/* Variables and functions */
 int /*<<< orphan*/  ML_HB_BIO ; 
 int O2HB_REGION_TIMEOUT_MS ; 
 void* cpu_to_le32 (int) ; 
 void* cpu_to_le64 (int) ; 
 int ktime_get_real_seconds () ; 
 int /*<<< orphan*/  le32_to_cpu (void*) ; 
 int /*<<< orphan*/  memset (struct o2hb_disk_heartbeat_block*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlog (int /*<<< orphan*/ ,char*,long long,int /*<<< orphan*/ ) ; 
 int o2hb_compute_block_crc_le (struct o2hb_region*,struct o2hb_disk_heartbeat_block*) ; 
 int o2hb_dead_threshold ; 
 int o2nm_this_node () ; 

__attribute__((used)) static inline void o2hb_prepare_block(struct o2hb_region *reg,
				      u64 generation)
{
	int node_num;
	u64 cputime;
	struct o2hb_disk_slot *slot;
	struct o2hb_disk_heartbeat_block *hb_block;

	node_num = o2nm_this_node();
	slot = &reg->hr_slots[node_num];

	hb_block = (struct o2hb_disk_heartbeat_block *)slot->ds_raw_block;
	memset(hb_block, 0, reg->hr_block_bytes);
	/* TODO: time stuff */
	cputime = ktime_get_real_seconds();
	if (!cputime)
		cputime = 1;

	hb_block->hb_seq = cpu_to_le64(cputime);
	hb_block->hb_node = node_num;
	hb_block->hb_generation = cpu_to_le64(generation);
	hb_block->hb_dead_ms = cpu_to_le32(o2hb_dead_threshold * O2HB_REGION_TIMEOUT_MS);

	/* This step must always happen last! */
	hb_block->hb_cksum = cpu_to_le32(o2hb_compute_block_crc_le(reg,
								   hb_block));

	mlog(ML_HB_BIO, "our node generation = 0x%llx, cksum = 0x%x\n",
	     (long long)generation,
	     le32_to_cpu(hb_block->hb_cksum));
}