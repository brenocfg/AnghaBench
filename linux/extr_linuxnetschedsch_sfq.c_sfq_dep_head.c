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
struct sfq_sched_data {struct sfq_head* dep; TYPE_1__* slots; } ;
struct sfq_head {int dummy; } ;
typedef  size_t sfq_index ;
struct TYPE_2__ {struct sfq_head dep; } ;

/* Variables and functions */
 size_t SFQ_MAX_FLOWS ; 

__attribute__((used)) static inline struct sfq_head *sfq_dep_head(struct sfq_sched_data *q, sfq_index val)
{
	if (val < SFQ_MAX_FLOWS)
		return &q->slots[val].dep;
	return &q->dep[val - SFQ_MAX_FLOWS];
}