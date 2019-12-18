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
struct jffs2_sb_info {int sector_size; } ;
struct jffs2_raw_node_ref {int dummy; } ;
struct jffs2_inode_cache {int dummy; } ;
struct jffs2_eraseblock {int free_size; scalar_t__ offset; } ;

/* Variables and functions */
 struct jffs2_raw_node_ref* jffs2_link_node_ref (struct jffs2_sb_info*,struct jffs2_eraseblock*,scalar_t__,int,struct jffs2_inode_cache*) ; 
 int /*<<< orphan*/  jffs2_scan_dirty_space (struct jffs2_sb_info*,struct jffs2_eraseblock*,int) ; 

__attribute__((used)) static struct jffs2_raw_node_ref *sum_link_node_ref(struct jffs2_sb_info *c,
						    struct jffs2_eraseblock *jeb,
						    uint32_t ofs, uint32_t len,
						    struct jffs2_inode_cache *ic)
{
	/* If there was a gap, mark it dirty */
	if ((ofs & ~3) > c->sector_size - jeb->free_size) {
		/* Ew. Summary doesn't actually tell us explicitly about dirty space */
		jffs2_scan_dirty_space(c, jeb, (ofs & ~3) - (c->sector_size - jeb->free_size));
	}

	return jffs2_link_node_ref(c, jeb, jeb->offset + ofs, len, ic);
}