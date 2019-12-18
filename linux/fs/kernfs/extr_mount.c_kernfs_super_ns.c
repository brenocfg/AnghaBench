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
struct kernfs_super_info {void const* ns; } ;

/* Variables and functions */
 struct kernfs_super_info* kernfs_info (struct super_block*) ; 

const void *kernfs_super_ns(struct super_block *sb)
{
	struct kernfs_super_info *info = kernfs_info(sb);

	return info->ns;
}