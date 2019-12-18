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
typedef  int /*<<< orphan*/  u32 ;
struct cls_fl_head {int /*<<< orphan*/  handle_idr; } ;
struct cls_fl_filter {int /*<<< orphan*/  refcnt; } ;

/* Variables and functions */
 struct cls_fl_filter* idr_find (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 
 int /*<<< orphan*/  refcount_inc_not_zero (int /*<<< orphan*/ *) ; 

__attribute__((used)) static struct cls_fl_filter *__fl_get(struct cls_fl_head *head, u32 handle)
{
	struct cls_fl_filter *f;

	rcu_read_lock();
	f = idr_find(&head->handle_idr, handle);
	if (f && !refcount_inc_not_zero(&f->refcnt))
		f = NULL;
	rcu_read_unlock();

	return f;
}