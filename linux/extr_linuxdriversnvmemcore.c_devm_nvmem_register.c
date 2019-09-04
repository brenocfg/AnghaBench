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
struct nvmem_device {int dummy; } ;
struct nvmem_config {int dummy; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENOMEM ; 
 struct nvmem_device* ERR_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IS_ERR (struct nvmem_device*) ; 
 int /*<<< orphan*/  devm_nvmem_release ; 
 int /*<<< orphan*/  devres_add (struct device*,struct nvmem_device**) ; 
 struct nvmem_device** devres_alloc (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  devres_free (struct nvmem_device**) ; 
 struct nvmem_device* nvmem_register (struct nvmem_config const*) ; 

struct nvmem_device *devm_nvmem_register(struct device *dev,
					 const struct nvmem_config *config)
{
	struct nvmem_device **ptr, *nvmem;

	ptr = devres_alloc(devm_nvmem_release, sizeof(*ptr), GFP_KERNEL);
	if (!ptr)
		return ERR_PTR(-ENOMEM);

	nvmem = nvmem_register(config);

	if (!IS_ERR(nvmem)) {
		*ptr = nvmem;
		devres_add(dev, ptr);
	} else {
		devres_free(ptr);
	}

	return nvmem;
}