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
typedef  scalar_t__ uint64_t ;
struct TYPE_3__ {scalar_t__ transition_start_time; scalar_t__ transition_duration; } ;
typedef  TYPE_1__ obs_source_t ;

/* Variables and functions */

__attribute__((used)) static float calc_time(obs_source_t *transition, uint64_t ts)
{
	uint64_t end;

	if (ts <= transition->transition_start_time)
		return 0.0f;

	end = transition->transition_duration;
	ts -= transition->transition_start_time;
	if (ts >= end || end == 0)
		return 1.0f;

	return (float)((long double)ts / (long double)end);
}