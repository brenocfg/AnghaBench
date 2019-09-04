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
typedef  size_t u16 ;
struct btrfs_super_block {int dummy; } ;

/* Variables and functions */
 int* btrfs_csum_sizes ; 
 size_t btrfs_super_csum_type (struct btrfs_super_block const*) ; 

__attribute__((used)) static inline int btrfs_super_csum_size(const struct btrfs_super_block *s)
{
	u16 t = btrfs_super_csum_type(s);
	/*
	 * csum type is validated at mount time
	 */
	return btrfs_csum_sizes[t];
}