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
 int /*<<< orphan*/  __this_cpu_dec (int /*<<< orphan*/ ) ; 
 TYPE_1__ context_tracking ; 

__attribute__((used)) static void context_tracking_recursion_exit(void)
{
	__this_cpu_dec(context_tracking.recursion);
}