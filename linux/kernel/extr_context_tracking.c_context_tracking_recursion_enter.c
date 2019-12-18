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
struct TYPE_2__ {int /*<<< orphan*/  recursion; } ;

/* Variables and functions */
 int /*<<< orphan*/  WARN_ONCE (int,char*,int) ; 
 int /*<<< orphan*/  __this_cpu_dec (int /*<<< orphan*/ ) ; 
 int __this_cpu_inc_return (int /*<<< orphan*/ ) ; 
 TYPE_1__ context_tracking ; 

__attribute__((used)) static bool context_tracking_recursion_enter(void)
{
	int recursion;

	recursion = __this_cpu_inc_return(context_tracking.recursion);
	if (recursion == 1)
		return true;

	WARN_ONCE((recursion < 1), "Invalid context tracking recursion value %d\n", recursion);
	__this_cpu_dec(context_tracking.recursion);

	return false;
}