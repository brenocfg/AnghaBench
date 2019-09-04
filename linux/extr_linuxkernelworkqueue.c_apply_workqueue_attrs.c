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
struct workqueue_struct {int dummy; } ;
struct workqueue_attrs {int dummy; } ;

/* Variables and functions */
 int apply_workqueue_attrs_locked (struct workqueue_struct*,struct workqueue_attrs const*) ; 
 int /*<<< orphan*/  apply_wqattrs_lock () ; 
 int /*<<< orphan*/  apply_wqattrs_unlock () ; 

int apply_workqueue_attrs(struct workqueue_struct *wq,
			  const struct workqueue_attrs *attrs)
{
	int ret;

	apply_wqattrs_lock();
	ret = apply_workqueue_attrs_locked(wq, attrs);
	apply_wqattrs_unlock();

	return ret;
}