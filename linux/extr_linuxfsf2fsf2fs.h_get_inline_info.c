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
struct f2fs_inode_info {int /*<<< orphan*/  flags; } ;
struct f2fs_inode {int i_inline; } ;

/* Variables and functions */
 int F2FS_DATA_EXIST ; 
 int F2FS_EXTRA_ATTR ; 
 struct f2fs_inode_info* F2FS_I (struct inode*) ; 
 int F2FS_INLINE_DATA ; 
 int F2FS_INLINE_DENTRY ; 
 int F2FS_INLINE_DOTS ; 
 int F2FS_INLINE_XATTR ; 
 int F2FS_PIN_FILE ; 
 int /*<<< orphan*/  FI_DATA_EXIST ; 
 int /*<<< orphan*/  FI_EXTRA_ATTR ; 
 int /*<<< orphan*/  FI_INLINE_DATA ; 
 int /*<<< orphan*/  FI_INLINE_DENTRY ; 
 int /*<<< orphan*/  FI_INLINE_DOTS ; 
 int /*<<< orphan*/  FI_INLINE_XATTR ; 
 int /*<<< orphan*/  FI_PIN_FILE ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline void get_inline_info(struct inode *inode, struct f2fs_inode *ri)
{
	struct f2fs_inode_info *fi = F2FS_I(inode);

	if (ri->i_inline & F2FS_INLINE_XATTR)
		set_bit(FI_INLINE_XATTR, &fi->flags);
	if (ri->i_inline & F2FS_INLINE_DATA)
		set_bit(FI_INLINE_DATA, &fi->flags);
	if (ri->i_inline & F2FS_INLINE_DENTRY)
		set_bit(FI_INLINE_DENTRY, &fi->flags);
	if (ri->i_inline & F2FS_DATA_EXIST)
		set_bit(FI_DATA_EXIST, &fi->flags);
	if (ri->i_inline & F2FS_INLINE_DOTS)
		set_bit(FI_INLINE_DOTS, &fi->flags);
	if (ri->i_inline & F2FS_EXTRA_ATTR)
		set_bit(FI_EXTRA_ATTR, &fi->flags);
	if (ri->i_inline & F2FS_PIN_FILE)
		set_bit(FI_PIN_FILE, &fi->flags);
}