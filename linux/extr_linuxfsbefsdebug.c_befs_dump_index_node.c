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
struct super_block {int dummy; } ;
typedef  int /*<<< orphan*/  befs_btree_nodehead ;

/* Variables and functions */

void
befs_dump_index_node(const struct super_block *sb, befs_btree_nodehead *node)
{
#ifdef CONFIG_BEFS_DEBUG

	befs_debug(sb, "Btree node structure");
	befs_debug(sb, "  left %016LX", fs64_to_cpu(sb, node->left));
	befs_debug(sb, "  right %016LX", fs64_to_cpu(sb, node->right));
	befs_debug(sb, "  overflow %016LX", fs64_to_cpu(sb, node->overflow));
	befs_debug(sb, "  all_key_count %hu",
		   fs16_to_cpu(sb, node->all_key_count));
	befs_debug(sb, "  all_key_length %hu",
		   fs16_to_cpu(sb, node->all_key_length));

#endif				//CONFIG_BEFS_DEBUG
}