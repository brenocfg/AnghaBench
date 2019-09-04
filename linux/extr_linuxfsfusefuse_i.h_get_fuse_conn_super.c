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
struct super_block {struct fuse_conn* s_fs_info; } ;
struct fuse_conn {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static inline struct fuse_conn *get_fuse_conn_super(struct super_block *sb)
{
	return sb->s_fs_info;
}