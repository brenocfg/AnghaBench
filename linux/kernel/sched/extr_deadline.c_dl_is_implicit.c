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
struct sched_dl_entity {scalar_t__ dl_deadline; scalar_t__ dl_period; } ;

/* Variables and functions */

__attribute__((used)) static inline bool dl_is_implicit(struct sched_dl_entity *dl_se)
{
	return dl_se->dl_deadline == dl_se->dl_period;
}