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
struct inode {unsigned long i_blkbits; } ;

/* Variables and functions */
 unsigned long BITS_PER_LONG ; 

__attribute__((used)) static inline unsigned long
nilfs_palloc_groups_count(const struct inode *inode)
{
	return 1UL << (BITS_PER_LONG - (inode->i_blkbits + 3 /* log2(8) */));
}