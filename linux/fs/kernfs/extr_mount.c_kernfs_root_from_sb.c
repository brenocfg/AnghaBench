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
struct super_block {int /*<<< orphan*/ * s_op; } ;
struct kernfs_root {int dummy; } ;
struct TYPE_2__ {struct kernfs_root* root; } ;

/* Variables and functions */
 TYPE_1__* kernfs_info (struct super_block*) ; 
 int /*<<< orphan*/  kernfs_sops ; 

struct kernfs_root *kernfs_root_from_sb(struct super_block *sb)
{
	if (sb->s_op == &kernfs_sops)
		return kernfs_info(sb)->root;
	return NULL;
}