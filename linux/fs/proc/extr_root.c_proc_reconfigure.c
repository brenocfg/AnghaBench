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
struct super_block {struct pid_namespace* s_fs_info; } ;
struct pid_namespace {int dummy; } ;
struct fs_context {TYPE_1__* root; } ;
struct TYPE_2__ {struct super_block* d_sb; } ;

/* Variables and functions */
 int /*<<< orphan*/  current_user_ns () ; 
 int /*<<< orphan*/  proc_apply_options (struct super_block*,struct fs_context*,struct pid_namespace*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sync_filesystem (struct super_block*) ; 

__attribute__((used)) static int proc_reconfigure(struct fs_context *fc)
{
	struct super_block *sb = fc->root->d_sb;
	struct pid_namespace *pid = sb->s_fs_info;

	sync_filesystem(sb);

	proc_apply_options(sb, fc, pid, current_user_ns());
	return 0;
}