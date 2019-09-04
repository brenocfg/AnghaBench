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
struct TYPE_3__ {scalar_t__ last_frame_ts; } ;
typedef  TYPE_1__ obs_source_t ;

/* Variables and functions */
 scalar_t__ MAX_TS_VAR ; 

__attribute__((used)) static inline bool frame_out_of_bounds(const obs_source_t *source, uint64_t ts)
{
	if (ts < source->last_frame_ts)
		return ((source->last_frame_ts - ts) > MAX_TS_VAR);
	else
		return ((ts - source->last_frame_ts) > MAX_TS_VAR);
}