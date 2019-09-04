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
struct sched_dl_entity {int /*<<< orphan*/  rb_node; } ;

/* Variables and functions */
 int /*<<< orphan*/  RB_EMPTY_NODE (int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline int on_dl_rq(struct sched_dl_entity *dl_se)
{
	return !RB_EMPTY_NODE(&dl_se->rb_node);
}