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
typedef  int uint32_t ;
struct jffs2_mount_opts {int rp_size; } ;
struct jffs2_sb_info {int resv_blocks_write; int sector_size; int nospc_dirty_size; int /*<<< orphan*/  nr_erasing_blocks; int /*<<< orphan*/  unchecked_size; int /*<<< orphan*/  erasing_size; scalar_t__ free_size; scalar_t__ dirty_size; struct jffs2_mount_opts mount_opts; } ;

/* Variables and functions */
 int /*<<< orphan*/  CAP_SYS_RESOURCE ; 
 scalar_t__ capable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jffs2_dbg (int,char*,...) ; 

__attribute__((used)) static int jffs2_rp_can_write(struct jffs2_sb_info *c)
{
	uint32_t avail;
	struct jffs2_mount_opts *opts = &c->mount_opts;

	avail = c->dirty_size + c->free_size + c->unchecked_size +
		c->erasing_size - c->resv_blocks_write * c->sector_size
		- c->nospc_dirty_size;

	if (avail < 2 * opts->rp_size)
		jffs2_dbg(1, "rpsize %u, dirty_size %u, free_size %u, "
			  "erasing_size %u, unchecked_size %u, "
			  "nr_erasing_blocks %u, avail %u, resrv %u\n",
			  opts->rp_size, c->dirty_size, c->free_size,
			  c->erasing_size, c->unchecked_size,
			  c->nr_erasing_blocks, avail, c->nospc_dirty_size);

	if (avail > opts->rp_size)
		return 1;

	/* Always allow root */
	if (capable(CAP_SYS_RESOURCE))
		return 1;

	jffs2_dbg(1, "forbid writing\n");
	return 0;
}