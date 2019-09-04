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
struct fq_flow_head {struct fq_flow* last; struct fq_flow* first; } ;
struct fq_flow {struct fq_flow* next; } ;

/* Variables and functions */

__attribute__((used)) static void fq_flow_add_tail(struct fq_flow_head *head, struct fq_flow *flow)
{
	if (head->first)
		head->last->next = flow;
	else
		head->first = flow;
	head->last = flow;
	flow->next = NULL;
}