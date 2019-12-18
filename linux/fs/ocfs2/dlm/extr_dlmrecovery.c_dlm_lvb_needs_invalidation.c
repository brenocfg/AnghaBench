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
struct TYPE_2__ {scalar_t__ type; } ;
struct dlm_lock {TYPE_1__ ml; } ;

/* Variables and functions */
 scalar_t__ LKM_EXMODE ; 
 scalar_t__ LKM_PRMODE ; 

__attribute__((used)) static inline int dlm_lvb_needs_invalidation(struct dlm_lock *lock, int local)
{
	if (local) {
		if (lock->ml.type != LKM_EXMODE &&
		    lock->ml.type != LKM_PRMODE)
			return 1;
	} else if (lock->ml.type == LKM_EXMODE)
		return 1;
	return 0;
}