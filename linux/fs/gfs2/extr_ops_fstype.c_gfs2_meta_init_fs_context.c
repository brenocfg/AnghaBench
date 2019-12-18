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
struct fs_context {int /*<<< orphan*/ * ops; } ;

/* Variables and functions */
 int gfs2_init_fs_context (struct fs_context*) ; 
 int /*<<< orphan*/  gfs2_meta_context_ops ; 

__attribute__((used)) static int gfs2_meta_init_fs_context(struct fs_context *fc)
{
	int ret = gfs2_init_fs_context(fc);

	if (ret)
		return ret;

	fc->ops = &gfs2_meta_context_ops;
	return 0;
}