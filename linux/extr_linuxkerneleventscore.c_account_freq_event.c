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
 int /*<<< orphan*/  account_freq_event_nohz () ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nr_freq_events ; 
 scalar_t__ tick_nohz_full_enabled () ; 

__attribute__((used)) static void account_freq_event(void)
{
	if (tick_nohz_full_enabled())
		account_freq_event_nohz();
	else
		atomic_inc(&nr_freq_events);
}