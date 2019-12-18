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
typedef  int u64 ;
struct taprio_sched {int /*<<< orphan*/  picos_per_byte; } ;
struct sched_entry {scalar_t__ interval; int /*<<< orphan*/  budget; } ;

/* Variables and functions */
 int /*<<< orphan*/  atomic64_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  div64_u64 (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void taprio_set_budget(struct taprio_sched *q, struct sched_entry *entry)
{
	atomic_set(&entry->budget,
		   div64_u64((u64)entry->interval * 1000,
			     atomic64_read(&q->picos_per_byte)));
}