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
typedef  int u_long ;
struct super_block {int s_blocksize; } ;
typedef  int daddr_t ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 

__attribute__((used)) static inline u_long
vxfs_oblock(struct super_block *sbp, daddr_t block, u_long bsize)
{
	BUG_ON(sbp->s_blocksize % bsize);
	return (block * (sbp->s_blocksize / bsize));
}