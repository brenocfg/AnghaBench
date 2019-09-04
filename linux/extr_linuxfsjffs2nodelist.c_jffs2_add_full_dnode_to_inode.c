#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct jffs2_sb_info {int dummy; } ;
struct jffs2_node_frag {int ofs; int size; TYPE_1__* node; } ;
struct jffs2_inode_info {int /*<<< orphan*/  fragtree; } ;
struct jffs2_full_dnode {int /*<<< orphan*/  raw; scalar_t__ size; scalar_t__ ofs; } ;
struct TYPE_2__ {int frags; int /*<<< orphan*/  raw; } ;

/* Variables and functions */
 int ENOMEM ; 
 int PAGE_SIZE ; 
 int /*<<< orphan*/  dbg_fragtree (char*,scalar_t__,scalar_t__,int /*<<< orphan*/ ,struct jffs2_node_frag*) ; 
 struct jffs2_node_frag* frag_next (struct jffs2_node_frag*) ; 
 struct jffs2_node_frag* frag_prev (struct jffs2_node_frag*) ; 
 int jffs2_add_frag_to_fragtree (struct jffs2_sb_info*,int /*<<< orphan*/ *,struct jffs2_node_frag*) ; 
 int /*<<< orphan*/  jffs2_dbg_fragtree_paranoia_check_nolock (struct jffs2_inode_info*) ; 
 int /*<<< orphan*/  mark_ref_normal (int /*<<< orphan*/ ) ; 
 struct jffs2_node_frag* new_fragment (struct jffs2_full_dnode*,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  ref_offset (int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int) ; 

int jffs2_add_full_dnode_to_inode(struct jffs2_sb_info *c, struct jffs2_inode_info *f, struct jffs2_full_dnode *fn)
{
	int ret;
	struct jffs2_node_frag *newfrag;

	if (unlikely(!fn->size))
		return 0;

	newfrag = new_fragment(fn, fn->ofs, fn->size);
	if (unlikely(!newfrag))
		return -ENOMEM;
	newfrag->node->frags = 1;

	dbg_fragtree("adding node %#04x-%#04x @0x%08x on flash, newfrag *%p\n",
		  fn->ofs, fn->ofs+fn->size, ref_offset(fn->raw), newfrag);

	ret = jffs2_add_frag_to_fragtree(c, &f->fragtree, newfrag);
	if (unlikely(ret))
		return ret;

	/* If we now share a page with other nodes, mark either previous
	   or next node REF_NORMAL, as appropriate.  */
	if (newfrag->ofs & (PAGE_SIZE-1)) {
		struct jffs2_node_frag *prev = frag_prev(newfrag);

		mark_ref_normal(fn->raw);
		/* If we don't start at zero there's _always_ a previous */
		if (prev->node)
			mark_ref_normal(prev->node->raw);
	}

	if ((newfrag->ofs+newfrag->size) & (PAGE_SIZE-1)) {
		struct jffs2_node_frag *next = frag_next(newfrag);

		if (next) {
			mark_ref_normal(fn->raw);
			if (next->node)
				mark_ref_normal(next->node->raw);
		}
	}
	jffs2_dbg_fragtree_paranoia_check_nolock(f);

	return 0;
}