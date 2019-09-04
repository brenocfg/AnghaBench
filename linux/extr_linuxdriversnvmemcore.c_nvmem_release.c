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
struct nvmem_device {int /*<<< orphan*/  id; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ida_simple_remove (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct nvmem_device*) ; 
 int /*<<< orphan*/  nvmem_ida ; 
 struct nvmem_device* to_nvmem_device (struct device*) ; 

__attribute__((used)) static void nvmem_release(struct device *dev)
{
	struct nvmem_device *nvmem = to_nvmem_device(dev);

	ida_simple_remove(&nvmem_ida, nvmem->id);
	kfree(nvmem);
}