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
struct work_struct {int dummy; } ;
struct dummy {int /*<<< orphan*/  list; } ;

/* Variables and functions */
 int ALLOC_PERIOD ; 
 int /*<<< orphan*/  alloc_dwork ; 
 struct dummy* dummy_alloc () ; 
 int /*<<< orphan*/  dummy_list ; 
 int /*<<< orphan*/  dummy_list_mutex ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  msecs_to_jiffies (int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  schedule_delayed_work (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void alloc_work_func(struct work_struct *work)
{
	struct dummy *d;

	d = dummy_alloc();
	if (!d)
		return;

	mutex_lock(&dummy_list_mutex);
	list_add(&d->list, &dummy_list);
	mutex_unlock(&dummy_list_mutex);

	schedule_delayed_work(&alloc_dwork,
		msecs_to_jiffies(1000 * ALLOC_PERIOD));
}