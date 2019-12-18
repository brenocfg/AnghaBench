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
struct the_nilfs {int /*<<< orphan*/  ns_cno; } ;
struct inode {TYPE_1__* i_sb; } ;
typedef  int /*<<< orphan*/  __u64 ;
struct TYPE_2__ {scalar_t__ s_fs_info; } ;

/* Variables and functions */

__attribute__((used)) static inline __u64 nilfs_mdt_cno(struct inode *inode)
{
	return ((struct the_nilfs *)inode->i_sb->s_fs_info)->ns_cno;
}