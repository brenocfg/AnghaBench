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
typedef  int u32 ;

/* Variables and functions */
 int AA_X_UNSAFE ; 

__attribute__((used)) static inline bool xindex_is_subset(u32 link, u32 target)
{
	if (((link & ~AA_X_UNSAFE) != (target & ~AA_X_UNSAFE)) ||
	    ((link & AA_X_UNSAFE) && !(target & AA_X_UNSAFE)))
		return 0;

	return 1;
}