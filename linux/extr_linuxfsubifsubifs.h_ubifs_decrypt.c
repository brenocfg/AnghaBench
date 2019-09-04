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
struct ubifs_info {int dummy; } ;
struct ubifs_data_node {int dummy; } ;
struct inode {TYPE_1__* i_sb; } ;
struct TYPE_2__ {struct ubifs_info* s_fs_info; } ;

/* Variables and functions */
 int EOPNOTSUPP ; 
 int /*<<< orphan*/  ubifs_assert (struct ubifs_info*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline int ubifs_decrypt(const struct inode *inode,
				struct ubifs_data_node *dn,
				unsigned int *out_len, int block)
{
	struct ubifs_info *c = inode->i_sb->s_fs_info;
	ubifs_assert(c, 0);
	return -EOPNOTSUPP;
}