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
struct nvmem_device {int /*<<< orphan*/  users; int /*<<< orphan*/  owner; } ;

/* Variables and functions */
 int /*<<< orphan*/  module_put (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nvmem_mutex ; 

__attribute__((used)) static void __nvmem_device_put(struct nvmem_device *nvmem)
{
	module_put(nvmem->owner);
	mutex_lock(&nvmem_mutex);
	nvmem->users--;
	mutex_unlock(&nvmem_mutex);
}