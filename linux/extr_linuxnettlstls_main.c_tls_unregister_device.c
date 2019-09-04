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
struct tls_device {int /*<<< orphan*/  dev_list; } ;

/* Variables and functions */
 int /*<<< orphan*/  device_mutex ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

void tls_unregister_device(struct tls_device *device)
{
	mutex_lock(&device_mutex);
	list_del(&device->dev_list);
	mutex_unlock(&device_mutex);
}