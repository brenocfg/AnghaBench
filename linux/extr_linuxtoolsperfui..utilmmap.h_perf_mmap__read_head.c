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
typedef  int /*<<< orphan*/  u64 ;
struct perf_mmap {struct perf_event_mmap_page* base; } ;
struct perf_event_mmap_page {int /*<<< orphan*/  data_head; } ;

/* Variables and functions */
 int /*<<< orphan*/  READ_ONCE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rmb () ; 

__attribute__((used)) static inline u64 perf_mmap__read_head(struct perf_mmap *mm)
{
	struct perf_event_mmap_page *pc = mm->base;
	u64 head = READ_ONCE(pc->data_head);
	rmb();
	return head;
}