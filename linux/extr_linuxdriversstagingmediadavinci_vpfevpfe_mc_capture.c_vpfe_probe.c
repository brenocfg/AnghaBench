#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_6__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {int /*<<< orphan*/  model; TYPE_4__* dev; } ;
struct TYPE_9__ {TYPE_6__* mdev; } ;
struct vpfe_device {TYPE_6__ media_dev; TYPE_2__ v4l2_dev; struct vpfe_device* sd; TYPE_4__* pdev; int /*<<< orphan*/  imp_dma_irq; int /*<<< orphan*/  ccdc_irq1; int /*<<< orphan*/  ccdc_irq0; TYPE_1__* cfg; } ;
struct resource {int /*<<< orphan*/  start; } ;
struct TYPE_10__ {int /*<<< orphan*/  driver; TYPE_1__* platform_data; } ;
struct platform_device {TYPE_4__ dev; } ;
struct TYPE_8__ {int /*<<< orphan*/ * sub_devs; int /*<<< orphan*/ * card_name; } ;

/* Variables and functions */
 int ENOENT ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IORESOURCE_IRQ ; 
 struct vpfe_device* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kzfree (struct vpfe_device*) ; 
 int media_device_register (TYPE_6__*) ; 
 int /*<<< orphan*/  media_device_unregister (TYPE_6__*) ; 
 struct resource* platform_get_resource (struct platform_device*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct vpfe_device*) ; 
 int /*<<< orphan*/  strcpy (char*,char*) ; 
 int v4l2_device_register (TYPE_4__*,TYPE_2__*) ; 
 int /*<<< orphan*/  v4l2_device_unregister (TYPE_2__*) ; 
 int /*<<< orphan*/  v4l2_err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  v4l2_info (TYPE_2__*,char*) ; 
 int vpfe_attach_irq (struct vpfe_device*) ; 
 int /*<<< orphan*/  vpfe_cleanup_modules (struct vpfe_device*,struct platform_device*) ; 
 int /*<<< orphan*/  vpfe_disable_clock (struct vpfe_device*) ; 
 int vpfe_enable_clock (struct vpfe_device*) ; 
 int vpfe_initialize_modules (struct vpfe_device*,struct platform_device*) ; 
 int vpfe_register_entities (struct vpfe_device*) ; 
 int /*<<< orphan*/  vpfe_unregister_entities (struct vpfe_device*) ; 

__attribute__((used)) static int vpfe_probe(struct platform_device *pdev)
{
	struct vpfe_device *vpfe_dev;
	struct resource *res1;
	int ret = -ENOMEM;

	vpfe_dev = kzalloc(sizeof(*vpfe_dev), GFP_KERNEL);
	if (!vpfe_dev)
		return ret;

	if (pdev->dev.platform_data == NULL) {
		v4l2_err(pdev->dev.driver, "Unable to get vpfe config\n");
		ret = -ENOENT;
		goto probe_free_dev_mem;
	}

	vpfe_dev->cfg = pdev->dev.platform_data;
	if (vpfe_dev->cfg->card_name == NULL ||
			vpfe_dev->cfg->sub_devs == NULL) {
		v4l2_err(pdev->dev.driver, "null ptr in vpfe_cfg\n");
		ret = -ENOENT;
		goto probe_free_dev_mem;
	}

	/* Get VINT0 irq resource */
	res1 = platform_get_resource(pdev, IORESOURCE_IRQ, 0);
	if (!res1) {
		v4l2_err(pdev->dev.driver,
			 "Unable to get interrupt for VINT0\n");
		ret = -ENOENT;
		goto probe_free_dev_mem;
	}
	vpfe_dev->ccdc_irq0 = res1->start;

	/* Get VINT1 irq resource */
	res1 = platform_get_resource(pdev, IORESOURCE_IRQ, 1);
	if (!res1) {
		v4l2_err(pdev->dev.driver,
			 "Unable to get interrupt for VINT1\n");
		ret = -ENOENT;
		goto probe_free_dev_mem;
	}
	vpfe_dev->ccdc_irq1 = res1->start;

	/* Get DMA irq resource */
	res1 = platform_get_resource(pdev, IORESOURCE_IRQ, 2);
	if (!res1) {
		v4l2_err(pdev->dev.driver,
			 "Unable to get interrupt for DMA\n");
		ret = -ENOENT;
		goto probe_free_dev_mem;
	}
	vpfe_dev->imp_dma_irq = res1->start;

	vpfe_dev->pdev = &pdev->dev;

	/* enable vpss clocks */
	ret = vpfe_enable_clock(vpfe_dev);
	if (ret)
		goto probe_free_dev_mem;

	ret = vpfe_initialize_modules(vpfe_dev, pdev);
	if (ret)
		goto probe_disable_clock;

	vpfe_dev->media_dev.dev = vpfe_dev->pdev;
	strcpy((char *)&vpfe_dev->media_dev.model, "davinci-media");

	ret = media_device_register(&vpfe_dev->media_dev);
	if (ret) {
		v4l2_err(pdev->dev.driver,
			"Unable to register media device.\n");
		goto probe_out_entities_cleanup;
	}

	vpfe_dev->v4l2_dev.mdev = &vpfe_dev->media_dev;
	ret = v4l2_device_register(&pdev->dev, &vpfe_dev->v4l2_dev);
	if (ret) {
		v4l2_err(pdev->dev.driver, "Unable to register v4l2 device.\n");
		goto probe_out_media_unregister;
	}

	v4l2_info(&vpfe_dev->v4l2_dev, "v4l2 device registered\n");
	/* set the driver data in platform device */
	platform_set_drvdata(pdev, vpfe_dev);
	/* register subdevs/entities */
	ret = vpfe_register_entities(vpfe_dev);
	if (ret)
		goto probe_out_v4l2_unregister;

	ret = vpfe_attach_irq(vpfe_dev);
	if (ret)
		goto probe_out_entities_unregister;

	return 0;

probe_out_entities_unregister:
	vpfe_unregister_entities(vpfe_dev);
	kzfree(vpfe_dev->sd);
probe_out_v4l2_unregister:
	v4l2_device_unregister(&vpfe_dev->v4l2_dev);
probe_out_media_unregister:
	media_device_unregister(&vpfe_dev->media_dev);
probe_out_entities_cleanup:
	vpfe_cleanup_modules(vpfe_dev, pdev);
probe_disable_clock:
	vpfe_disable_clock(vpfe_dev);
probe_free_dev_mem:
	kzfree(vpfe_dev);

	return ret;
}