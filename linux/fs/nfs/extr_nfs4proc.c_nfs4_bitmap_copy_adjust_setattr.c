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
typedef  int /*<<< orphan*/  __u32 ;

/* Variables and functions */
 int /*<<< orphan*/  nfs4_bitmap_copy_adjust (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,struct inode*) ; 

__attribute__((used)) static void nfs4_bitmap_copy_adjust_setattr(__u32 *dst,
		const __u32 *src, struct inode *inode)
{
	nfs4_bitmap_copy_adjust(dst, src, inode);
}