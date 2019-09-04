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
#define  MADV_DODUMP 140 
#define  MADV_DOFORK 139 
#define  MADV_DONTDUMP 138 
#define  MADV_DONTFORK 137 
#define  MADV_DONTNEED 136 
#define  MADV_FREE 135 
#define  MADV_KEEPONFORK 134 
#define  MADV_NORMAL 133 
#define  MADV_RANDOM 132 
#define  MADV_REMOVE 131 
#define  MADV_SEQUENTIAL 130 
#define  MADV_WILLNEED 129 
#define  MADV_WIPEONFORK 128 

__attribute__((used)) static bool
madvise_behavior_valid(int behavior)
{
	switch (behavior) {
	case MADV_DOFORK:
	case MADV_DONTFORK:
	case MADV_NORMAL:
	case MADV_SEQUENTIAL:
	case MADV_RANDOM:
	case MADV_REMOVE:
	case MADV_WILLNEED:
	case MADV_DONTNEED:
	case MADV_FREE:
#ifdef CONFIG_KSM
	case MADV_MERGEABLE:
	case MADV_UNMERGEABLE:
#endif
#ifdef CONFIG_TRANSPARENT_HUGEPAGE
	case MADV_HUGEPAGE:
	case MADV_NOHUGEPAGE:
#endif
	case MADV_DONTDUMP:
	case MADV_DODUMP:
	case MADV_WIPEONFORK:
	case MADV_KEEPONFORK:
#ifdef CONFIG_MEMORY_FAILURE
	case MADV_SOFT_OFFLINE:
	case MADV_HWPOISON:
#endif
		return true;

	default:
		return false;
	}
}