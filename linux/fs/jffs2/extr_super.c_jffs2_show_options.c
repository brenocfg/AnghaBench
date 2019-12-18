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
struct seq_file {int dummy; } ;
struct jffs2_mount_opts {int rp_size; int /*<<< orphan*/  compr; scalar_t__ override_compr; } ;
struct jffs2_sb_info {struct jffs2_mount_opts mount_opts; } ;
struct dentry {int /*<<< orphan*/  d_sb; } ;

/* Variables and functions */
 struct jffs2_sb_info* JFFS2_SB_INFO (int /*<<< orphan*/ ) ; 
 int jffs2_compr_name (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  seq_printf (struct seq_file*,char*,int) ; 

__attribute__((used)) static int jffs2_show_options(struct seq_file *s, struct dentry *root)
{
	struct jffs2_sb_info *c = JFFS2_SB_INFO(root->d_sb);
	struct jffs2_mount_opts *opts = &c->mount_opts;

	if (opts->override_compr)
		seq_printf(s, ",compr=%s", jffs2_compr_name(opts->compr));
	if (opts->rp_size)
		seq_printf(s, ",rp_size=%u", opts->rp_size / 1024);

	return 0;
}