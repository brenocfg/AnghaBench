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
struct atm_ioctl {int /*<<< orphan*/  list; } ;

/* Variables and functions */
 int /*<<< orphan*/  ioctl_mutex ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

void deregister_atm_ioctl(struct atm_ioctl *ioctl)
{
	mutex_lock(&ioctl_mutex);
	list_del(&ioctl->list);
	mutex_unlock(&ioctl_mutex);
}