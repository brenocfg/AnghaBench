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
struct super_block {int dummy; } ;
struct fs_context {struct fs_context* source; int /*<<< orphan*/  fs_type; int /*<<< orphan*/  cred; int /*<<< orphan*/  user_ns; int /*<<< orphan*/  net_ns; int /*<<< orphan*/  security; TYPE_1__* ops; scalar_t__ need_free; TYPE_2__* root; } ;
struct TYPE_4__ {struct super_block* d_sb; } ;
struct TYPE_3__ {int /*<<< orphan*/  (* free ) (struct fs_context*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  deactivate_super (struct super_block*) ; 
 int /*<<< orphan*/  dput (TYPE_2__*) ; 
 int /*<<< orphan*/  kfree (struct fs_context*) ; 
 int /*<<< orphan*/  put_cred (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  put_fc_log (struct fs_context*) ; 
 int /*<<< orphan*/  put_filesystem (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  put_net (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  put_user_ns (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  security_free_mnt_opts (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (struct fs_context*) ; 

void put_fs_context(struct fs_context *fc)
{
	struct super_block *sb;

	if (fc->root) {
		sb = fc->root->d_sb;
		dput(fc->root);
		fc->root = NULL;
		deactivate_super(sb);
	}

	if (fc->need_free && fc->ops && fc->ops->free)
		fc->ops->free(fc);

	security_free_mnt_opts(&fc->security);
	put_net(fc->net_ns);
	put_user_ns(fc->user_ns);
	put_cred(fc->cred);
	put_fc_log(fc);
	put_filesystem(fc->fs_type);
	kfree(fc->source);
	kfree(fc);
}