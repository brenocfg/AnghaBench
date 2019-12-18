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
 int /*<<< orphan*/  evlist__disable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  evsel_list ; 
 int /*<<< orphan*/  target ; 
 int /*<<< orphan*/  target__none (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void disable_counters(void)
{
	/*
	 * If we don't have tracee (attaching to task or cpu), counters may
	 * still be running. To get accurate group ratios, we must stop groups
	 * from counting before reading their constituent counters.
	 */
	if (!target__none(&target))
		evlist__disable(evsel_list);
}