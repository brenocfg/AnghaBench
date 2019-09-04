#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct ext4_ext_path {int p_depth; TYPE_1__* p_idx; int /*<<< orphan*/  p_hdr; TYPE_2__* p_ext; } ;
typedef  int /*<<< orphan*/  ext4_lblk_t ;
struct TYPE_4__ {int /*<<< orphan*/  ee_block; } ;
struct TYPE_3__ {int /*<<< orphan*/  ei_block; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int /*<<< orphan*/ ) ; 
 TYPE_2__* EXT_LAST_EXTENT (int /*<<< orphan*/ ) ; 
 TYPE_1__* EXT_LAST_INDEX (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EXT_MAX_BLOCKS ; 
 int /*<<< orphan*/  le32_to_cpu (int /*<<< orphan*/ ) ; 

ext4_lblk_t
ext4_ext_next_allocated_block(struct ext4_ext_path *path)
{
	int depth;

	BUG_ON(path == NULL);
	depth = path->p_depth;

	if (depth == 0 && path->p_ext == NULL)
		return EXT_MAX_BLOCKS;

	while (depth >= 0) {
		if (depth == path->p_depth) {
			/* leaf */
			if (path[depth].p_ext &&
				path[depth].p_ext !=
					EXT_LAST_EXTENT(path[depth].p_hdr))
			  return le32_to_cpu(path[depth].p_ext[1].ee_block);
		} else {
			/* index */
			if (path[depth].p_idx !=
					EXT_LAST_INDEX(path[depth].p_hdr))
			  return le32_to_cpu(path[depth].p_idx[1].ei_block);
		}
		depth--;
	}

	return EXT_MAX_BLOCKS;
}