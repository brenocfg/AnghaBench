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

/* Variables and functions */
 int /*<<< orphan*/  KOBJ_NS_TYPE_NET ; 
 int /*<<< orphan*/  kernfs_kill_sb (struct super_block*) ; 
 scalar_t__ kernfs_super_ns (struct super_block*) ; 
 int /*<<< orphan*/  kobj_ns_drop (int /*<<< orphan*/ ,void*) ; 

__attribute__((used)) static void sysfs_kill_sb(struct super_block *sb)
{
	void *ns = (void *)kernfs_super_ns(sb);

	kernfs_kill_sb(sb);
	kobj_ns_drop(KOBJ_NS_TYPE_NET, ns);
}