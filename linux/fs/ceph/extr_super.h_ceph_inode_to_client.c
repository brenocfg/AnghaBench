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
struct inode {TYPE_1__* i_sb; } ;
struct ceph_fs_client {int dummy; } ;
struct TYPE_2__ {scalar_t__ s_fs_info; } ;

/* Variables and functions */

__attribute__((used)) static inline struct ceph_fs_client *ceph_inode_to_client(struct inode *inode)
{
	return (struct ceph_fs_client *)inode->i_sb->s_fs_info;
}