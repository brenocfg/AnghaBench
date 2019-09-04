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
struct f2fs_inode {int /*<<< orphan*/  i_inline; } ;

/* Variables and functions */
 int /*<<< orphan*/  F2FS_DATA_EXIST ; 
 int /*<<< orphan*/  F2FS_EXTRA_ATTR ; 
 int /*<<< orphan*/  F2FS_INLINE_DATA ; 
 int /*<<< orphan*/  F2FS_INLINE_DENTRY ; 
 int /*<<< orphan*/  F2FS_INLINE_DOTS ; 
 int /*<<< orphan*/  F2FS_INLINE_XATTR ; 
 int /*<<< orphan*/  F2FS_PIN_FILE ; 
 int /*<<< orphan*/  FI_DATA_EXIST ; 
 int /*<<< orphan*/  FI_EXTRA_ATTR ; 
 int /*<<< orphan*/  FI_INLINE_DATA ; 
 int /*<<< orphan*/  FI_INLINE_DENTRY ; 
 int /*<<< orphan*/  FI_INLINE_DOTS ; 
 int /*<<< orphan*/  FI_INLINE_XATTR ; 
 int /*<<< orphan*/  FI_PIN_FILE ; 
 scalar_t__ is_inode_flag_set (struct inode*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void set_raw_inline(struct inode *inode, struct f2fs_inode *ri)
{
	ri->i_inline = 0;

	if (is_inode_flag_set(inode, FI_INLINE_XATTR))
		ri->i_inline |= F2FS_INLINE_XATTR;
	if (is_inode_flag_set(inode, FI_INLINE_DATA))
		ri->i_inline |= F2FS_INLINE_DATA;
	if (is_inode_flag_set(inode, FI_INLINE_DENTRY))
		ri->i_inline |= F2FS_INLINE_DENTRY;
	if (is_inode_flag_set(inode, FI_DATA_EXIST))
		ri->i_inline |= F2FS_DATA_EXIST;
	if (is_inode_flag_set(inode, FI_INLINE_DOTS))
		ri->i_inline |= F2FS_INLINE_DOTS;
	if (is_inode_flag_set(inode, FI_EXTRA_ATTR))
		ri->i_inline |= F2FS_EXTRA_ATTR;
	if (is_inode_flag_set(inode, FI_PIN_FILE))
		ri->i_inline |= F2FS_PIN_FILE;
}