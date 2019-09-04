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
struct f2fs_inode {int i_inline; int /*<<< orphan*/  i_extra_isize; } ;
typedef  int /*<<< orphan*/  __le32 ;

/* Variables and functions */
 int F2FS_EXTRA_ATTR ; 
 int le16_to_cpu (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline int offset_in_addr(struct f2fs_inode *i)
{
	return (i->i_inline & F2FS_EXTRA_ATTR) ?
			(le16_to_cpu(i->i_extra_isize) / sizeof(__le32)) : 0;
}