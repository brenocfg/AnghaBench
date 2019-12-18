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

/* Variables and functions */
#define  FI_DATA_EXIST 134 
#define  FI_INLINE_DATA 133 
#define  FI_INLINE_DENTRY 132 
#define  FI_INLINE_DOTS 131 
#define  FI_INLINE_XATTR 130 
#define  FI_NEW_INODE 129 
#define  FI_PIN_FILE 128 
 int /*<<< orphan*/  f2fs_mark_inode_dirty_sync (struct inode*,int) ; 

__attribute__((used)) static inline void __mark_inode_dirty_flag(struct inode *inode,
						int flag, bool set)
{
	switch (flag) {
	case FI_INLINE_XATTR:
	case FI_INLINE_DATA:
	case FI_INLINE_DENTRY:
	case FI_NEW_INODE:
		if (set)
			return;
		/* fall through */
	case FI_DATA_EXIST:
	case FI_INLINE_DOTS:
	case FI_PIN_FILE:
		f2fs_mark_inode_dirty_sync(inode, true);
	}
}