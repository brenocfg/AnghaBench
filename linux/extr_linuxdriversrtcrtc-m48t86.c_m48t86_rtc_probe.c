#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct resource {int dummy; } ;
struct platform_device {int /*<<< orphan*/  dev; } ;
struct nvmem_config {char* name; int word_size; int stride; int /*<<< orphan*/ * priv; int /*<<< orphan*/  reg_write; int /*<<< orphan*/  reg_read; int /*<<< orphan*/  size; } ;
struct m48t86_rtc_info {TYPE_1__* rtc; TYPE_1__* data_reg; TYPE_1__* index_reg; } ;
struct TYPE_6__ {int nvram_old_abi; int /*<<< orphan*/ * ops; } ;

/* Variables and functions */
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IORESOURCE_MEM ; 
 scalar_t__ IS_ERR (TYPE_1__*) ; 
 int /*<<< orphan*/  M48T86_D ; 
 unsigned char M48T86_D_VRT ; 
 int /*<<< orphan*/  M48T86_NVRAM_LEN ; 
 int PTR_ERR (TYPE_1__*) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/  dev_set_drvdata (int /*<<< orphan*/ *,struct m48t86_rtc_info*) ; 
 void* devm_ioremap_resource (int /*<<< orphan*/ *,struct resource*) ; 
 struct m48t86_rtc_info* devm_kzalloc (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 TYPE_1__* devm_rtc_allocate_device (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  m48t86_nvram_read ; 
 int /*<<< orphan*/  m48t86_nvram_write ; 
 unsigned char m48t86_readb (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  m48t86_rtc_ops ; 
 int /*<<< orphan*/  m48t86_verify_chip (struct platform_device*) ; 
 struct resource* platform_get_resource (struct platform_device*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  rtc_nvmem_register (TYPE_1__*,struct nvmem_config*) ; 
 int rtc_register_device (TYPE_1__*) ; 

__attribute__((used)) static int m48t86_rtc_probe(struct platform_device *pdev)
{
	struct m48t86_rtc_info *info;
	struct resource *res;
	unsigned char reg;
	int err;
	struct nvmem_config m48t86_nvmem_cfg = {
		.name = "m48t86_nvram",
		.word_size = 1,
		.stride = 1,
		.size = M48T86_NVRAM_LEN,
		.reg_read = m48t86_nvram_read,
		.reg_write = m48t86_nvram_write,
		.priv = &pdev->dev,
	};

	info = devm_kzalloc(&pdev->dev, sizeof(*info), GFP_KERNEL);
	if (!info)
		return -ENOMEM;

	res = platform_get_resource(pdev, IORESOURCE_MEM, 0);
	if (!res)
		return -ENODEV;
	info->index_reg = devm_ioremap_resource(&pdev->dev, res);
	if (IS_ERR(info->index_reg))
		return PTR_ERR(info->index_reg);

	res = platform_get_resource(pdev, IORESOURCE_MEM, 1);
	if (!res)
		return -ENODEV;
	info->data_reg = devm_ioremap_resource(&pdev->dev, res);
	if (IS_ERR(info->data_reg))
		return PTR_ERR(info->data_reg);

	dev_set_drvdata(&pdev->dev, info);

	if (!m48t86_verify_chip(pdev)) {
		dev_info(&pdev->dev, "RTC not present\n");
		return -ENODEV;
	}

	info->rtc = devm_rtc_allocate_device(&pdev->dev);
	if (IS_ERR(info->rtc))
		return PTR_ERR(info->rtc);

	info->rtc->ops = &m48t86_rtc_ops;
	info->rtc->nvram_old_abi = true;

	err = rtc_register_device(info->rtc);
	if (err)
		return err;

	rtc_nvmem_register(info->rtc, &m48t86_nvmem_cfg);

	/* read battery status */
	reg = m48t86_readb(&pdev->dev, M48T86_D);
	dev_info(&pdev->dev, "battery %s\n",
		 (reg & M48T86_D_VRT) ? "ok" : "exhausted");

	return 0;
}