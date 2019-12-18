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
struct bp_busy_slots {int pinned; } ;

/* Variables and functions */

__attribute__((used)) static void
fetch_this_slot(struct bp_busy_slots *slots, int weight)
{
	slots->pinned += weight;
}