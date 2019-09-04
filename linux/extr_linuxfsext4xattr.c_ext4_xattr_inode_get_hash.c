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
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_2__ {int /*<<< orphan*/  tv_sec; } ;
struct inode {TYPE_1__ i_atime; } ;

/* Variables and functions */

__attribute__((used)) static u32 ext4_xattr_inode_get_hash(struct inode *ea_inode)
{
	return (u32)ea_inode->i_atime.tv_sec;
}