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
typedef  scalar_t__ u64 ;
typedef  int /*<<< orphan*/  u32 ;

/* Variables and functions */
 scalar_t__ BTRFS_MAX_EXTENT_SIZE ; 
 int /*<<< orphan*/  div_u64 (scalar_t__,scalar_t__) ; 

__attribute__((used)) static inline u32 count_max_extents(u64 size)
{
	return div_u64(size + BTRFS_MAX_EXTENT_SIZE - 1, BTRFS_MAX_EXTENT_SIZE);
}