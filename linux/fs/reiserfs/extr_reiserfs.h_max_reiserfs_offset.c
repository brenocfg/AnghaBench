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
struct inode {int dummy; } ;
typedef  int /*<<< orphan*/  loff_t ;
typedef  int __u64 ;

/* Variables and functions */
 scalar_t__ KEY_FORMAT_3_5 ; 
 int /*<<< orphan*/  U32_MAX ; 
 scalar_t__ get_inode_item_key_version (struct inode*) ; 

__attribute__((used)) static inline loff_t max_reiserfs_offset(struct inode *inode)
{
	if (get_inode_item_key_version(inode) == KEY_FORMAT_3_5)
		return (loff_t) U32_MAX;

	return (loff_t) ((~(__u64) 0) >> 4);
}