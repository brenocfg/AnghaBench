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
struct jffs2_tmp_dnode_info {TYPE_1__* fn; } ;
struct jffs2_sb_info {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  raw; scalar_t__ size; scalar_t__ ofs; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  JFFS2_ERROR (char*,int) ; 
 scalar_t__ REF_UNCHECKED ; 
 int check_node_data (struct jffs2_sb_info*,struct jffs2_tmp_dnode_info*) ; 
 int /*<<< orphan*/  dbg_readinode (char*,...) ; 
 int /*<<< orphan*/  jffs2_mark_node_obsolete (struct jffs2_sb_info*,int /*<<< orphan*/ ) ; 
 scalar_t__ ref_flags (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ref_obsolete (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ref_offset (int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int check_tn_node(struct jffs2_sb_info *c, struct jffs2_tmp_dnode_info *tn)
{
	int ret;

	BUG_ON(ref_obsolete(tn->fn->raw));

	/* We only check the data CRC of unchecked nodes */
	if (ref_flags(tn->fn->raw) != REF_UNCHECKED)
		return 0;

	dbg_readinode("check node %#04x-%#04x, phys offs %#08x\n",
		      tn->fn->ofs, tn->fn->ofs + tn->fn->size, ref_offset(tn->fn->raw));

	ret = check_node_data(c, tn);
	if (unlikely(ret < 0)) {
		JFFS2_ERROR("check_node_data() returned error: %d.\n",
			ret);
	} else if (unlikely(ret > 0)) {
		dbg_readinode("CRC error, mark it obsolete.\n");
		jffs2_mark_node_obsolete(c, tn->fn->raw);
	}

	return ret;
}