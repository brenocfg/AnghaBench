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
typedef  size_t u16 ;
struct btrfs_super_block {int dummy; } ;
struct TYPE_2__ {int size; } ;

/* Variables and functions */
 TYPE_1__* btrfs_csums ; 
 size_t btrfs_super_csum_type (struct btrfs_super_block const*) ; 

int btrfs_super_csum_size(const struct btrfs_super_block *s)
{
	u16 t = btrfs_super_csum_type(s);
	/*
	 * csum type is validated at mount time
	 */
	return btrfs_csums[t].size;
}