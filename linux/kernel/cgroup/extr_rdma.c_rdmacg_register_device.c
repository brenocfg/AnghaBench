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
struct rdmacg_device {int /*<<< orphan*/  dev_node; int /*<<< orphan*/  rpools; } ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rdmacg_devices ; 
 int /*<<< orphan*/  rdmacg_mutex ; 

void rdmacg_register_device(struct rdmacg_device *device)
{
	INIT_LIST_HEAD(&device->dev_node);
	INIT_LIST_HEAD(&device->rpools);

	mutex_lock(&rdmacg_mutex);
	list_add_tail(&device->dev_node, &rdmacg_devices);
	mutex_unlock(&rdmacg_mutex);
}