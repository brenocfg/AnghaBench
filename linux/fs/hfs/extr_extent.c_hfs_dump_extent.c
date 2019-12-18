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
struct hfs_extent {int /*<<< orphan*/  count; int /*<<< orphan*/  block; } ;

/* Variables and functions */
 int /*<<< orphan*/  EXTENT ; 
 int /*<<< orphan*/  be16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hfs_dbg (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  hfs_dbg_cont (int /*<<< orphan*/ ,char*,...) ; 

__attribute__((used)) static void hfs_dump_extent(struct hfs_extent *extent)
{
	int i;

	hfs_dbg(EXTENT, "   ");
	for (i = 0; i < 3; i++)
		hfs_dbg_cont(EXTENT, " %u:%u",
			     be16_to_cpu(extent[i].block),
			     be16_to_cpu(extent[i].count));
	hfs_dbg_cont(EXTENT, "\n");
}