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
struct task_struct {unsigned int il_prev; } ;
struct TYPE_2__ {int /*<<< orphan*/  nodes; } ;
struct mempolicy {TYPE_1__ v; } ;

/* Variables and functions */
 unsigned int MAX_NUMNODES ; 
 struct task_struct* current ; 
 unsigned int next_node_in (unsigned int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static unsigned interleave_nodes(struct mempolicy *policy)
{
	unsigned next;
	struct task_struct *me = current;

	next = next_node_in(me->il_prev, policy->v.nodes);
	if (next < MAX_NUMNODES)
		me->il_prev = next;
	return next;
}