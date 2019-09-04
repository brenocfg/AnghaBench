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
 int /*<<< orphan*/  jiffies ; 
 int time_after (int /*<<< orphan*/ ,unsigned long) ; 

__attribute__((used)) static bool past_time(unsigned long then)
{
	if (!then)
		/* 0 is a special value meaning "this never expires": */
		return false;
	return time_after(jiffies, then);
}