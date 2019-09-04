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
struct jffs2_sb_info {int dummy; } ;
struct jffs2_raw_node_ref {scalar_t__ flash_offset; struct jffs2_raw_node_ref* next_in_ino; } ;
struct jffs2_eraseblock {int /*<<< orphan*/ * last_node; struct jffs2_raw_node_ref* first_node; int /*<<< orphan*/  offset; } ;

/* Variables and functions */
 scalar_t__ REF_EMPTY_NODE ; 
 scalar_t__ REF_LINK_NODE ; 
 int /*<<< orphan*/  jffs2_dbg (int,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jffs2_free_refblock (struct jffs2_raw_node_ref*) ; 
 int /*<<< orphan*/  jffs2_remove_node_refs_from_ino_list (struct jffs2_sb_info*,struct jffs2_raw_node_ref*,struct jffs2_eraseblock*) ; 

void jffs2_free_jeb_node_refs(struct jffs2_sb_info *c, struct jffs2_eraseblock *jeb)
{
	struct jffs2_raw_node_ref *block, *ref;
	jffs2_dbg(1, "Freeing all node refs for eraseblock offset 0x%08x\n",
		  jeb->offset);

	block = ref = jeb->first_node;

	while (ref) {
		if (ref->flash_offset == REF_LINK_NODE) {
			ref = ref->next_in_ino;
			jffs2_free_refblock(block);
			block = ref;
			continue;
		}
		if (ref->flash_offset != REF_EMPTY_NODE && ref->next_in_ino)
			jffs2_remove_node_refs_from_ino_list(c, ref, jeb);
		/* else it was a non-inode node or already removed, so don't bother */

		ref++;
	}
	jeb->first_node = jeb->last_node = NULL;
}