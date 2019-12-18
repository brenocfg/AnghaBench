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
struct nilfs_bmap {int dummy; } ;
typedef  scalar_t__ __u64 ;

/* Variables and functions */
 scalar_t__ NILFS_BMAP_INVALID_PTR ; 
 scalar_t__ nilfs_bmap_find_target_in_group (struct nilfs_bmap const*) ; 
 scalar_t__ nilfs_bmap_find_target_seq (struct nilfs_bmap const*,scalar_t__) ; 

__attribute__((used)) static __u64
nilfs_direct_find_target_v(const struct nilfs_bmap *direct, __u64 key)
{
	__u64 ptr;

	ptr = nilfs_bmap_find_target_seq(direct, key);
	if (ptr != NILFS_BMAP_INVALID_PTR)
		/* sequential access */
		return ptr;

	/* block group */
	return nilfs_bmap_find_target_in_group(direct);
}