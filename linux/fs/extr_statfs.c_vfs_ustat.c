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
struct super_block {int /*<<< orphan*/  s_root; } ;
struct kstatfs {int dummy; } ;
typedef  int /*<<< orphan*/  dev_t ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  drop_super (struct super_block*) ; 
 int statfs_by_dentry (int /*<<< orphan*/ ,struct kstatfs*) ; 
 struct super_block* user_get_super (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int vfs_ustat(dev_t dev, struct kstatfs *sbuf)
{
	struct super_block *s = user_get_super(dev);
	int err;
	if (!s)
		return -EINVAL;

	err = statfs_by_dentry(s->s_root, sbuf);
	drop_super(s);
	return err;
}