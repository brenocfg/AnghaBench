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
typedef  int /*<<< orphan*/  __le32 ;

/* Variables and functions */
 scalar_t__ f2fs_has_inline_xattr (struct inode*) ; 
 int get_inline_xattr_addrs (struct inode*) ; 

__attribute__((used)) static inline int inline_xattr_size(struct inode *inode)
{
	if (f2fs_has_inline_xattr(inode))
		return get_inline_xattr_addrs(inode) * sizeof(__le32);
	return 0;
}