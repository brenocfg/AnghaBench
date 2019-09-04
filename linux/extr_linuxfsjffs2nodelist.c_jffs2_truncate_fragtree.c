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
typedef  scalar_t__ uint32_t ;
struct rb_root {int dummy; } ;
struct jffs2_sb_info {int dummy; } ;
struct jffs2_node_frag {scalar_t__ ofs; scalar_t__ size; TYPE_1__* node; } ;
struct TYPE_4__ {int flash_offset; } ;
struct TYPE_3__ {TYPE_2__* raw; } ;

/* Variables and functions */
 int PAGE_SIZE ; 
 int REF_PRISTINE ; 
 int /*<<< orphan*/  dbg_fragtree (char*,scalar_t__) ; 
 int /*<<< orphan*/  dbg_fragtree2 (char*,int,scalar_t__) ; 
 int /*<<< orphan*/  frag_erase (struct jffs2_node_frag*,struct rb_root*) ; 
 struct jffs2_node_frag* frag_last (struct rb_root*) ; 
 struct jffs2_node_frag* frag_next (struct jffs2_node_frag*) ; 
 struct jffs2_node_frag* jffs2_lookup_node_frag (struct rb_root*,scalar_t__) ; 
 int /*<<< orphan*/  jffs2_obsolete_node_frag (struct jffs2_sb_info*,struct jffs2_node_frag*) ; 
 int ref_offset (TYPE_2__*) ; 

uint32_t jffs2_truncate_fragtree(struct jffs2_sb_info *c, struct rb_root *list, uint32_t size)
{
	struct jffs2_node_frag *frag = jffs2_lookup_node_frag(list, size);

	dbg_fragtree("truncating fragtree to 0x%08x bytes\n", size);

	/* We know frag->ofs <= size. That's what lookup does for us */
	if (frag && frag->ofs != size) {
		if (frag->ofs+frag->size > size) {
			frag->size = size - frag->ofs;
		}
		frag = frag_next(frag);
	}
	while (frag && frag->ofs >= size) {
		struct jffs2_node_frag *next = frag_next(frag);

		frag_erase(frag, list);
		jffs2_obsolete_node_frag(c, frag);
		frag = next;
	}

	if (size == 0)
		return 0;

	frag = frag_last(list);

	/* Sanity check for truncation to longer than we started with... */
	if (!frag)
		return 0;
	if (frag->ofs + frag->size < size)
		return frag->ofs + frag->size;

	/* If the last fragment starts at the RAM page boundary, it is
	 * REF_PRISTINE irrespective of its size. */
	if (frag->node && (frag->ofs & (PAGE_SIZE - 1)) == 0) {
		dbg_fragtree2("marking the last fragment 0x%08x-0x%08x REF_PRISTINE.\n",
			frag->ofs, frag->ofs + frag->size);
		frag->node->raw->flash_offset = ref_offset(frag->node->raw) | REF_PRISTINE;
	}
	return size;
}