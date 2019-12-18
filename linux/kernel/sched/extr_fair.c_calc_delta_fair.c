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
typedef  int /*<<< orphan*/  u64 ;
struct TYPE_2__ {scalar_t__ weight; } ;
struct sched_entity {TYPE_1__ load; } ;

/* Variables and functions */
 scalar_t__ NICE_0_LOAD ; 
 int /*<<< orphan*/  __calc_delta (int /*<<< orphan*/ ,scalar_t__,TYPE_1__*) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static inline u64 calc_delta_fair(u64 delta, struct sched_entity *se)
{
	if (unlikely(se->load.weight != NICE_0_LOAD))
		delta = __calc_delta(delta, NICE_0_LOAD, &se->load);

	return delta;
}