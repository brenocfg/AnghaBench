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
struct TYPE_3__ {scalar_t__ isReset; } ;
typedef  TYPE_1__* MemoryContext ;

/* Variables and functions */

__attribute__((used)) static bool
AllocSetIsEmpty(MemoryContext context)
{
	/*
	 * For now, we say "empty" only if the context is new or just reset. We
	 * could examine the freelists to determine if all space has been freed,
	 * but it's not really worth the trouble for present uses of this
	 * functionality.
	 */
	if (context->isReset)
		return true;
	return false;
}