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
struct jffs2_sb_info {int dummy; } ;
struct fs_context {int /*<<< orphan*/ * ops; struct jffs2_sb_info* s_fs_info; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  jffs2_context_ops ; 
 struct jffs2_sb_info* kzalloc (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int jffs2_init_fs_context(struct fs_context *fc)
{
	struct jffs2_sb_info *ctx;

	ctx = kzalloc(sizeof(struct jffs2_sb_info), GFP_KERNEL);
	if (!ctx)
		return -ENOMEM;

	fc->s_fs_info = ctx;
	fc->ops = &jffs2_context_ops;
	return 0;
}