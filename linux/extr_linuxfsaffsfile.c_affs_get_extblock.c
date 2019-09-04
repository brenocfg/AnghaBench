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
typedef  scalar_t__ u32 ;
struct inode {int dummy; } ;
struct buffer_head {int dummy; } ;
struct TYPE_2__ {scalar_t__ i_ext_last; struct buffer_head* i_ext_bh; } ;

/* Variables and functions */
 TYPE_1__* AFFS_I (struct inode*) ; 
 struct buffer_head* affs_get_extblock_slow (struct inode*,scalar_t__) ; 
 int /*<<< orphan*/  get_bh (struct buffer_head*) ; 

__attribute__((used)) static inline struct buffer_head *
affs_get_extblock(struct inode *inode, u32 ext)
{
	/* inline the simplest case: same extended block as last time */
	struct buffer_head *bh = AFFS_I(inode)->i_ext_bh;
	if (ext == AFFS_I(inode)->i_ext_last)
		get_bh(bh);
	else
		/* we have to do more (not inlined) */
		bh = affs_get_extblock_slow(inode, ext);

	return bh;
}