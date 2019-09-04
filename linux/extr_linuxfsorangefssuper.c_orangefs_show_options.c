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
struct seq_file {int dummy; } ;
struct orangefs_sb_info_s {int flags; } ;
struct dentry {TYPE_1__* d_sb; } ;
struct TYPE_2__ {int s_flags; } ;

/* Variables and functions */
 int ORANGEFS_OPT_INTR ; 
 int ORANGEFS_OPT_LOCAL_LOCK ; 
 struct orangefs_sb_info_s* ORANGEFS_SB (TYPE_1__*) ; 
 int SB_POSIXACL ; 
 int /*<<< orphan*/  seq_puts (struct seq_file*,char*) ; 

__attribute__((used)) static int orangefs_show_options(struct seq_file *m, struct dentry *root)
{
	struct orangefs_sb_info_s *orangefs_sb = ORANGEFS_SB(root->d_sb);

	if (root->d_sb->s_flags & SB_POSIXACL)
		seq_puts(m, ",acl");
	if (orangefs_sb->flags & ORANGEFS_OPT_INTR)
		seq_puts(m, ",intr");
	if (orangefs_sb->flags & ORANGEFS_OPT_LOCAL_LOCK)
		seq_puts(m, ",local_lock");
	return 0;
}