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
struct node_info {int /*<<< orphan*/  version; int /*<<< orphan*/  blk_addr; int /*<<< orphan*/  ino; } ;
struct f2fs_nat_entry {int /*<<< orphan*/  version; void* block_addr; void* ino; } ;

/* Variables and functions */
 void* cpu_to_le32 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void raw_nat_from_node_info(struct f2fs_nat_entry *raw_ne,
						struct node_info *ni)
{
	raw_ne->ino = cpu_to_le32(ni->ino);
	raw_ne->block_addr = cpu_to_le32(ni->blk_addr);
	raw_ne->version = ni->version;
}