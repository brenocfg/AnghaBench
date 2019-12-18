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
struct map_groups {TYPE_1__* unwind_libunwind_ops; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* finish_access ) (struct map_groups*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (struct map_groups*) ; 

void unwind__finish_access(struct map_groups *mg)
{
	if (mg->unwind_libunwind_ops)
		mg->unwind_libunwind_ops->finish_access(mg);
}