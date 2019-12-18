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
struct cond_av_list {struct cond_av_list* next; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct cond_av_list*) ; 

__attribute__((used)) static void cond_av_list_destroy(struct cond_av_list *list)
{
	struct cond_av_list *cur, *next;
	for (cur = list; cur; cur = next) {
		next = cur->next;
		/* the avtab_ptr_t node is destroy by the avtab */
		kfree(cur);
	}
}