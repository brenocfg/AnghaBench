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
 int /*<<< orphan*/  BITS_TO_LONGS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 unsigned long* kcalloc_node (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static inline unsigned long *
sd_zbc_alloc_zone_bitmap(u32 nr_zones, int numa_node)
{
	return kcalloc_node(BITS_TO_LONGS(nr_zones), sizeof(unsigned long),
			    GFP_KERNEL, numa_node);
}