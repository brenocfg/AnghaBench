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
typedef  int /*<<< orphan*/  uint32_t ;
struct jffs2_sb_info {int dummy; } ;
struct jffs2_raw_node_ref {int dummy; } ;
struct jffs2_eraseblock {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  __ref_totlen (struct jffs2_sb_info*,struct jffs2_eraseblock*,struct jffs2_raw_node_ref*) ; 

uint32_t __jffs2_ref_totlen(struct jffs2_sb_info *c, struct jffs2_eraseblock *jeb,
			    struct jffs2_raw_node_ref *ref)
{
	uint32_t ret;

	ret = __ref_totlen(c, jeb, ref);

#ifdef TEST_TOTLEN
	if (unlikely(ret != ref->__totlen)) {
		if (!jeb)
			jeb = &c->blocks[ref->flash_offset / c->sector_size];

		pr_crit("Totlen for ref at %p (0x%08x-0x%08x) miscalculated as 0x%x instead of %x\n",
			ref, ref_offset(ref), ref_offset(ref) + ref->__totlen,
			ret, ref->__totlen);
		if (ref_next(ref)) {
			pr_crit("next %p (0x%08x-0x%08x)\n",
				ref_next(ref), ref_offset(ref_next(ref)),
				ref_offset(ref_next(ref)) + ref->__totlen);
		} else 
			pr_crit("No next ref. jeb->last_node is %p\n",
				jeb->last_node);

		pr_crit("jeb->wasted_size %x, dirty_size %x, used_size %x, free_size %x\n",
			jeb->wasted_size, jeb->dirty_size, jeb->used_size,
			jeb->free_size);

#if defined(JFFS2_DBG_DUMPS) || defined(JFFS2_DBG_PARANOIA_CHECKS)
		__jffs2_dbg_dump_node_refs_nolock(c, jeb);
#endif

		WARN_ON(1);

		ret = ref->__totlen;
	}
#endif /* TEST_TOTLEN */
	return ret;
}