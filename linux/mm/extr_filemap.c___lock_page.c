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
typedef  int /*<<< orphan*/  wait_queue_head_t ;
struct page {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  EXCLUSIVE ; 
 int /*<<< orphan*/  PG_locked ; 
 int /*<<< orphan*/  TASK_UNINTERRUPTIBLE ; 
 struct page* compound_head (struct page*) ; 
 int /*<<< orphan*/ * page_waitqueue (struct page*) ; 
 int /*<<< orphan*/  wait_on_page_bit_common (int /*<<< orphan*/ *,struct page*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void __lock_page(struct page *__page)
{
	struct page *page = compound_head(__page);
	wait_queue_head_t *q = page_waitqueue(page);
	wait_on_page_bit_common(q, page, PG_locked, TASK_UNINTERRUPTIBLE,
				EXCLUSIVE);
}