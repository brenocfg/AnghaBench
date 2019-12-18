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
struct pseudo_fs_context {int /*<<< orphan*/ * dops; } ;
struct fs_context {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ANON_INODE_FS_MAGIC ; 
 int ENOMEM ; 
 int /*<<< orphan*/  anon_inodefs_dentry_operations ; 
 struct pseudo_fs_context* init_pseudo (struct fs_context*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int anon_inodefs_init_fs_context(struct fs_context *fc)
{
	struct pseudo_fs_context *ctx = init_pseudo(fc, ANON_INODE_FS_MAGIC);
	if (!ctx)
		return -ENOMEM;
	ctx->dops = &anon_inodefs_dentry_operations;
	return 0;
}