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
typedef  int /*<<< orphan*/  u32 ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 unsigned long* kvzalloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memalloc_nofs_restore (unsigned int) ; 
 unsigned int memalloc_nofs_save () ; 
 int /*<<< orphan*/  round_up (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static unsigned long *alloc_bitmap(u32 bitmap_size)
{
	unsigned long *ret;
	unsigned int nofs_flag;
	u32 bitmap_rounded_size = round_up(bitmap_size, sizeof(unsigned long));

	/*
	 * GFP_NOFS doesn't work with kvmalloc(), but we really can't recurse
	 * into the filesystem as the free space bitmap can be modified in the
	 * critical section of a transaction commit.
	 *
	 * TODO: push the memalloc_nofs_{save,restore}() to the caller where we
	 * know that recursion is unsafe.
	 */
	nofs_flag = memalloc_nofs_save();
	ret = kvzalloc(bitmap_rounded_size, GFP_KERNEL);
	memalloc_nofs_restore(nofs_flag);
	return ret;
}