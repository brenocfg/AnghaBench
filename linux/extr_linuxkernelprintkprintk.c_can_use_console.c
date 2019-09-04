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
 scalar_t__ cpu_online (int /*<<< orphan*/ ) ; 
 scalar_t__ have_callable_console () ; 
 int /*<<< orphan*/  raw_smp_processor_id () ; 

__attribute__((used)) static inline int can_use_console(void)
{
	return cpu_online(raw_smp_processor_id()) || have_callable_console();
}