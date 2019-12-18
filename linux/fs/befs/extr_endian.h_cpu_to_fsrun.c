#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_5__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct super_block {int dummy; } ;
struct TYPE_6__ {void* len; void* start; int /*<<< orphan*/  allocation_group; } ;
typedef  TYPE_1__ befs_disk_block_run ;
struct TYPE_7__ {int /*<<< orphan*/  len; int /*<<< orphan*/  start; int /*<<< orphan*/  allocation_group; } ;
typedef  TYPE_2__ befs_block_run ;
struct TYPE_8__ {scalar_t__ byte_order; } ;

/* Variables and functions */
 scalar_t__ BEFS_BYTESEX_LE ; 
 TYPE_5__* BEFS_SB (struct super_block const*) ; 
 void* cpu_to_be16 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpu_to_be32 (int /*<<< orphan*/ ) ; 
 void* cpu_to_le16 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpu_to_le32 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline befs_disk_block_run
cpu_to_fsrun(const struct super_block *sb, befs_block_run n)
{
	befs_disk_block_run run;

	if (BEFS_SB(sb)->byte_order == BEFS_BYTESEX_LE) {
		run.allocation_group = cpu_to_le32(n.allocation_group);
		run.start = cpu_to_le16(n.start);
		run.len = cpu_to_le16(n.len);
	} else {
		run.allocation_group = cpu_to_be32(n.allocation_group);
		run.start = cpu_to_be16(n.start);
		run.len = cpu_to_be16(n.len);
	}
	return run;
}