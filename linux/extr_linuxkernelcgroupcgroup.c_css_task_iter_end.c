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
struct css_task_iter {scalar_t__ cur_task; scalar_t__ cur_dcset; scalar_t__ cur_cset; int /*<<< orphan*/  iters_node; } ;

/* Variables and functions */
 int /*<<< orphan*/  css_set_lock ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  put_css_set (scalar_t__) ; 
 int /*<<< orphan*/  put_css_set_locked (scalar_t__) ; 
 int /*<<< orphan*/  put_task_struct (scalar_t__) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 

void css_task_iter_end(struct css_task_iter *it)
{
	if (it->cur_cset) {
		spin_lock_irq(&css_set_lock);
		list_del(&it->iters_node);
		put_css_set_locked(it->cur_cset);
		spin_unlock_irq(&css_set_lock);
	}

	if (it->cur_dcset)
		put_css_set(it->cur_dcset);

	if (it->cur_task)
		put_task_struct(it->cur_task);
}