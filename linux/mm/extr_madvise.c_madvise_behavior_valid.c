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
#define  MADV_COLD 148 
#define  MADV_DODUMP 147 
#define  MADV_DOFORK 146 
#define  MADV_DONTDUMP 145 
#define  MADV_DONTFORK 144 
#define  MADV_DONTNEED 143 
#define  MADV_FREE 142 
#define  MADV_HUGEPAGE 141 
#define  MADV_HWPOISON 140 
#define  MADV_KEEPONFORK 139 
#define  MADV_MERGEABLE 138 
#define  MADV_NOHUGEPAGE 137 
#define  MADV_NORMAL 136 
#define  MADV_PAGEOUT 135 
#define  MADV_RANDOM 134 
#define  MADV_REMOVE 133 
#define  MADV_SEQUENTIAL 132 
#define  MADV_SOFT_OFFLINE 131 
#define  MADV_UNMERGEABLE 130 
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
	case MADV_COLD:
	case MADV_PAGEOUT:
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