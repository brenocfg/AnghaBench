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
struct sched_dl_entity {scalar_t__ runtime; } ;

/* Variables and functions */

__attribute__((used)) static
int dl_runtime_exceeded(struct sched_dl_entity *dl_se)
{
	return (dl_se->runtime <= 0);
}