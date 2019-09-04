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
typedef  scalar_t__ u64 ;
struct sugov_cpu {scalar_t__ last_update; int iowait_boost_pending; int /*<<< orphan*/  min; int /*<<< orphan*/  iowait_boost; } ;
typedef  scalar_t__ s64 ;

/* Variables and functions */
 scalar_t__ TICK_NSEC ; 

__attribute__((used)) static bool sugov_iowait_reset(struct sugov_cpu *sg_cpu, u64 time,
			       bool set_iowait_boost)
{
	s64 delta_ns = time - sg_cpu->last_update;

	/* Reset boost only if a tick has elapsed since last request */
	if (delta_ns <= TICK_NSEC)
		return false;

	sg_cpu->iowait_boost = set_iowait_boost ? sg_cpu->min : 0;
	sg_cpu->iowait_boost_pending = set_iowait_boost;

	return true;
}