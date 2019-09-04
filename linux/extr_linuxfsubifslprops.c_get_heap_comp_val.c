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
struct ubifs_lprops {int free; int dirty; } ;

/* Variables and functions */
#define  LPROPS_DIRTY_IDX 129 
#define  LPROPS_FREE 128 

__attribute__((used)) static int get_heap_comp_val(struct ubifs_lprops *lprops, int cat)
{
	switch (cat) {
	case LPROPS_FREE:
		return lprops->free;
	case LPROPS_DIRTY_IDX:
		return lprops->free + lprops->dirty;
	default:
		return lprops->dirty;
	}
}