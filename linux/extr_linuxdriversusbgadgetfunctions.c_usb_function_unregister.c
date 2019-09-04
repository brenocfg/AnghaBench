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
struct usb_function_driver {int /*<<< orphan*/  list; } ;

/* Variables and functions */
 int /*<<< orphan*/  func_lock ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

void usb_function_unregister(struct usb_function_driver *fd)
{
	mutex_lock(&func_lock);
	list_del(&fd->list);
	mutex_unlock(&func_lock);
}