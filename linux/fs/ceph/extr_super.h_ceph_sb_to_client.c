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
struct super_block {scalar_t__ s_fs_info; } ;
struct ceph_fs_client {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static inline struct ceph_fs_client *ceph_sb_to_client(struct super_block *sb)
{
	return (struct ceph_fs_client *)sb->s_fs_info;
}