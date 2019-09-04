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
struct device {int dummy; } ;
struct platform_device {struct device dev; } ;
struct nvmem_device {int dummy; } ;
struct nvmem_config {int stride; int word_size; unsigned int size; int /*<<< orphan*/  reg_write; int /*<<< orphan*/  reg_read; int /*<<< orphan*/  name; struct device* dev; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int PTR_ERR_OR_ZERO (struct nvmem_device*) ; 
 int /*<<< orphan*/  SM_EFUSE_USER_MAX ; 
 int /*<<< orphan*/  dev_name (struct device*) ; 
 struct nvmem_config* devm_kzalloc (struct device*,int,int /*<<< orphan*/ ) ; 
 struct nvmem_device* devm_nvmem_register (struct device*,struct nvmem_config*) ; 
 int /*<<< orphan*/  meson_efuse_read ; 
 int /*<<< orphan*/  meson_efuse_write ; 
 scalar_t__ meson_sm_call (int /*<<< orphan*/ ,unsigned int*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int meson_efuse_probe(struct platform_device *pdev)
{
	struct device *dev = &pdev->dev;
	struct nvmem_device *nvmem;
	struct nvmem_config *econfig;
	unsigned int size;

	if (meson_sm_call(SM_EFUSE_USER_MAX, &size, 0, 0, 0, 0, 0) < 0)
		return -EINVAL;

	econfig = devm_kzalloc(dev, sizeof(*econfig), GFP_KERNEL);
	if (!econfig)
		return -ENOMEM;

	econfig->dev = dev;
	econfig->name = dev_name(dev);
	econfig->stride = 1;
	econfig->word_size = 1;
	econfig->reg_read = meson_efuse_read;
	econfig->reg_write = meson_efuse_write;
	econfig->size = size;

	nvmem = devm_nvmem_register(&pdev->dev, econfig);

	return PTR_ERR_OR_ZERO(nvmem);
}