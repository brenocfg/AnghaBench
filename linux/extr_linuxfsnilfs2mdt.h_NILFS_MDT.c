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
struct nilfs_mdt_info {int dummy; } ;
struct inode {struct nilfs_mdt_info* i_private; } ;

/* Variables and functions */

__attribute__((used)) static inline struct nilfs_mdt_info *NILFS_MDT(const struct inode *inode)
{
	return inode->i_private;
}