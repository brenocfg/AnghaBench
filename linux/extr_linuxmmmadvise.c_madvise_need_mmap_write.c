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

/* Variables and functions */
#define  MADV_DONTNEED 131 
#define  MADV_FREE 130 
#define  MADV_REMOVE 129 
#define  MADV_WILLNEED 128 

__attribute__((used)) static int madvise_need_mmap_write(int behavior)
{
	switch (behavior) {
	case MADV_REMOVE:
	case MADV_WILLNEED:
	case MADV_DONTNEED:
	case MADV_FREE:
		return 0;
	default:
		/* be safe, default to 1. list exceptions explicitly */
		return 1;
	}
}