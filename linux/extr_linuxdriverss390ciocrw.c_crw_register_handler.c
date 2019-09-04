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
typedef  scalar_t__ crw_handler_t ;

/* Variables and functions */
 int EBUSY ; 
 int EINVAL ; 
 int NR_RSCS ; 
 int /*<<< orphan*/  crw_handler_mutex ; 
 scalar_t__* crw_handlers ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

int crw_register_handler(int rsc, crw_handler_t handler)
{
	int rc = 0;

	if ((rsc < 0) || (rsc >= NR_RSCS))
		return -EINVAL;
	mutex_lock(&crw_handler_mutex);
	if (crw_handlers[rsc])
		rc = -EBUSY;
	else
		crw_handlers[rsc] = handler;
	mutex_unlock(&crw_handler_mutex);
	return rc;
}