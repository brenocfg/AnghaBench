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
struct net {int /*<<< orphan*/  user_ns; } ;
struct kernfs_fs_context {int /*<<< orphan*/  magic; int /*<<< orphan*/  root; struct net* ns_tag; } ;
struct fs_context {int sb_flags; int global; int /*<<< orphan*/  user_ns; int /*<<< orphan*/ * ops; struct kernfs_fs_context* fs_private; } ;

/* Variables and functions */
 int ENOMEM ; 
 int EPERM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  KOBJ_NS_TYPE_NET ; 
 int SB_KERNMOUNT ; 
 int /*<<< orphan*/  SYSFS_MAGIC ; 
 int /*<<< orphan*/  get_user_ns (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kobj_ns_current_may_mount (int /*<<< orphan*/ ) ; 
 struct net* kobj_ns_grab_current (int /*<<< orphan*/ ) ; 
 struct kernfs_fs_context* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  put_user_ns (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sysfs_fs_context_ops ; 
 int /*<<< orphan*/  sysfs_root ; 

__attribute__((used)) static int sysfs_init_fs_context(struct fs_context *fc)
{
	struct kernfs_fs_context *kfc;
	struct net *netns;

	if (!(fc->sb_flags & SB_KERNMOUNT)) {
		if (!kobj_ns_current_may_mount(KOBJ_NS_TYPE_NET))
			return -EPERM;
	}

	kfc = kzalloc(sizeof(struct kernfs_fs_context), GFP_KERNEL);
	if (!kfc)
		return -ENOMEM;

	kfc->ns_tag = netns = kobj_ns_grab_current(KOBJ_NS_TYPE_NET);
	kfc->root = sysfs_root;
	kfc->magic = SYSFS_MAGIC;
	fc->fs_private = kfc;
	fc->ops = &sysfs_fs_context_ops;
	if (netns) {
		put_user_ns(fc->user_ns);
		fc->user_ns = get_user_ns(netns->user_ns);
	}
	fc->global = true;
	return 0;
}