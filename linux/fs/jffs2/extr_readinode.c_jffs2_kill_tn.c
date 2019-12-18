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
struct TYPE_2__ {int /*<<< orphan*/  raw; } ;

/* Variables and functions */
 int /*<<< orphan*/  jffs2_free_full_dnode (TYPE_1__*) ; 
 int /*<<< orphan*/  jffs2_free_tmp_dnode_info (struct jffs2_tmp_dnode_info*) ; 
 int /*<<< orphan*/  jffs2_mark_node_obsolete (struct jffs2_sb_info*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void jffs2_kill_tn(struct jffs2_sb_info *c, struct jffs2_tmp_dnode_info *tn)
{
	jffs2_mark_node_obsolete(c, tn->fn->raw);
	jffs2_free_full_dnode(tn->fn);
	jffs2_free_tmp_dnode_info(tn);
}