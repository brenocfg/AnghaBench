#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  mr_lock; scalar_t__ mr_writer; } ;
typedef  TYPE_1__ mrlock_t ;

/* Variables and functions */
 int /*<<< orphan*/  downgrade_write (int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline void mrdemote(mrlock_t *mrp)
{
#if defined(DEBUG) || defined(XFS_WARN)
	mrp->mr_writer = 0;
#endif
	downgrade_write(&mrp->mr_lock);
}