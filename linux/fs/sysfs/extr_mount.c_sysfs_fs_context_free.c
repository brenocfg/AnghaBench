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
struct kernfs_fs_context {scalar_t__ ns_tag; } ;
struct fs_context {struct kernfs_fs_context* fs_private; } ;

/* Variables and functions */
 int /*<<< orphan*/  KOBJ_NS_TYPE_NET ; 
 int /*<<< orphan*/  kernfs_free_fs_context (struct fs_context*) ; 
 int /*<<< orphan*/  kfree (struct kernfs_fs_context*) ; 
 int /*<<< orphan*/  kobj_ns_drop (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void sysfs_fs_context_free(struct fs_context *fc)
{
	struct kernfs_fs_context *kfc = fc->fs_private;

	if (kfc->ns_tag)
		kobj_ns_drop(KOBJ_NS_TYPE_NET, kfc->ns_tag);
	kernfs_free_fs_context(fc);
	kfree(kfc);
}