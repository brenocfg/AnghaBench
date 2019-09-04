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
struct nilfs_bmap {int b_state; } ;

/* Variables and functions */
 int NILFS_BMAP_DIRTY ; 

__attribute__((used)) static inline int nilfs_bmap_dirty(const struct nilfs_bmap *bmap)
{
	return !!(bmap->b_state & NILFS_BMAP_DIRTY);
}