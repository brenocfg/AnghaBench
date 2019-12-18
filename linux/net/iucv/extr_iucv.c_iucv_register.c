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
struct iucv_handler {int /*<<< orphan*/  list; int /*<<< orphan*/  paths; } ;

/* Variables and functions */
 int ENOSYS ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  iucv_available ; 
 int iucv_enable () ; 
 int /*<<< orphan*/  iucv_handler_list ; 
 int iucv_nonsmp_handler ; 
 int /*<<< orphan*/  iucv_register_mutex ; 
 int /*<<< orphan*/  iucv_setmask_up () ; 
 int /*<<< orphan*/  iucv_table_lock ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 

int iucv_register(struct iucv_handler *handler, int smp)
{
	int rc;

	if (!iucv_available)
		return -ENOSYS;
	mutex_lock(&iucv_register_mutex);
	if (!smp)
		iucv_nonsmp_handler++;
	if (list_empty(&iucv_handler_list)) {
		rc = iucv_enable();
		if (rc)
			goto out_mutex;
	} else if (!smp && iucv_nonsmp_handler == 1)
		iucv_setmask_up();
	INIT_LIST_HEAD(&handler->paths);

	spin_lock_bh(&iucv_table_lock);
	list_add_tail(&handler->list, &iucv_handler_list);
	spin_unlock_bh(&iucv_table_lock);
	rc = 0;
out_mutex:
	mutex_unlock(&iucv_register_mutex);
	return rc;
}