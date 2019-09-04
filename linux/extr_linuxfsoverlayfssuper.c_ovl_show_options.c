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
struct super_block {struct ovl_fs* s_fs_info; } ;
struct seq_file {int dummy; } ;
struct TYPE_2__ {char* redirect_mode; scalar_t__ index; scalar_t__ nfs_export; size_t xino; scalar_t__ metacopy; scalar_t__ default_permissions; scalar_t__ workdir; scalar_t__ upperdir; scalar_t__ lowerdir; } ;
struct ovl_fs {TYPE_1__ config; } ;
struct dentry {struct super_block* d_sb; } ;

/* Variables and functions */
 scalar_t__ ovl_index_def ; 
 scalar_t__ ovl_metacopy_def ; 
 scalar_t__ ovl_nfs_export_def ; 
 int /*<<< orphan*/  ovl_redirect_mode_def () ; 
 size_t ovl_xino_def () ; 
 char** ovl_xino_str ; 
 int /*<<< orphan*/  seq_printf (struct seq_file*,char*,char*) ; 
 int /*<<< orphan*/  seq_puts (struct seq_file*,char*) ; 
 int /*<<< orphan*/  seq_show_option (struct seq_file*,char*,scalar_t__) ; 
 scalar_t__ strcmp (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ovl_show_options(struct seq_file *m, struct dentry *dentry)
{
	struct super_block *sb = dentry->d_sb;
	struct ovl_fs *ofs = sb->s_fs_info;

	seq_show_option(m, "lowerdir", ofs->config.lowerdir);
	if (ofs->config.upperdir) {
		seq_show_option(m, "upperdir", ofs->config.upperdir);
		seq_show_option(m, "workdir", ofs->config.workdir);
	}
	if (ofs->config.default_permissions)
		seq_puts(m, ",default_permissions");
	if (strcmp(ofs->config.redirect_mode, ovl_redirect_mode_def()) != 0)
		seq_printf(m, ",redirect_dir=%s", ofs->config.redirect_mode);
	if (ofs->config.index != ovl_index_def)
		seq_printf(m, ",index=%s", ofs->config.index ? "on" : "off");
	if (ofs->config.nfs_export != ovl_nfs_export_def)
		seq_printf(m, ",nfs_export=%s", ofs->config.nfs_export ?
						"on" : "off");
	if (ofs->config.xino != ovl_xino_def())
		seq_printf(m, ",xino=%s", ovl_xino_str[ofs->config.xino]);
	if (ofs->config.metacopy != ovl_metacopy_def)
		seq_printf(m, ",metacopy=%s",
			   ofs->config.metacopy ? "on" : "off");
	return 0;
}