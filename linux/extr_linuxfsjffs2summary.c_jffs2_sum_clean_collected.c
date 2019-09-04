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
struct TYPE_2__ {union jffs2_sum_mem* next; } ;
union jffs2_sum_mem {TYPE_1__ u; } ;
struct jffs2_summary {scalar_t__ sum_num; scalar_t__ sum_padded; int /*<<< orphan*/ * sum_list_tail; union jffs2_sum_mem* sum_list_head; } ;

/* Variables and functions */
 int /*<<< orphan*/  dbg_summary (char*) ; 
 int /*<<< orphan*/  kfree (union jffs2_sum_mem*) ; 

__attribute__((used)) static void jffs2_sum_clean_collected(struct jffs2_summary *s)
{
	union jffs2_sum_mem *temp;

	if (!s->sum_list_head) {
		dbg_summary("already empty\n");
	}
	while (s->sum_list_head) {
		temp = s->sum_list_head;
		s->sum_list_head = s->sum_list_head->u.next;
		kfree(temp);
	}
	s->sum_list_tail = NULL;
	s->sum_padded = 0;
	s->sum_num = 0;
}