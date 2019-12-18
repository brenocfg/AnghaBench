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
struct kernfs_fs_context {int /*<<< orphan*/ * ns_tag; } ;
struct fs_context {struct kernfs_fs_context* fs_private; } ;

/* Variables and functions */
 int set_anon_super_fc (struct super_block*,struct fs_context*) ; 

__attribute__((used)) static int kernfs_set_super(struct super_block *sb, struct fs_context *fc)
{
	struct kernfs_fs_context *kfc = fc->fs_private;

	kfc->ns_tag = NULL;
	return set_anon_super_fc(sb, fc);
}