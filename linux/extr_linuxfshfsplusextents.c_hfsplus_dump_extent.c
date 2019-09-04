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
struct hfsplus_extent {int /*<<< orphan*/  block_count; int /*<<< orphan*/  start_block; } ;

/* Variables and functions */
 int /*<<< orphan*/  EXTENT ; 
 int /*<<< orphan*/  be32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hfs_dbg (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  hfs_dbg_cont (int /*<<< orphan*/ ,char*,...) ; 

__attribute__((used)) static void hfsplus_dump_extent(struct hfsplus_extent *extent)
{
	int i;

	hfs_dbg(EXTENT, "   ");
	for (i = 0; i < 8; i++)
		hfs_dbg_cont(EXTENT, " %u:%u",
			     be32_to_cpu(extent[i].start_block),
			     be32_to_cpu(extent[i].block_count));
	hfs_dbg_cont(EXTENT, "\n");
}