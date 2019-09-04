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
struct platform_device {int /*<<< orphan*/  dev; } ;
struct bcm2835_codec_driver {int /*<<< orphan*/ * decode; int /*<<< orphan*/ * encode; int /*<<< orphan*/ * isp; } ;

/* Variables and functions */
 int /*<<< orphan*/  DECODE ; 
 int /*<<< orphan*/  ENCODE ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  ISP ; 
 int bcm2835_codec_create (struct platform_device*,int /*<<< orphan*/ **,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bcm2835_codec_destroy (int /*<<< orphan*/ *) ; 
 struct bcm2835_codec_driver* devm_kzalloc (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct bcm2835_codec_driver*) ; 

__attribute__((used)) static int bcm2835_codec_probe(struct platform_device *pdev)
{
	struct bcm2835_codec_driver *drv;
	int ret = 0;

	drv = devm_kzalloc(&pdev->dev, sizeof(*drv), GFP_KERNEL);
	if (!drv)
		return -ENOMEM;

	ret = bcm2835_codec_create(pdev, &drv->decode, DECODE);
	if (ret)
		goto out;

	ret = bcm2835_codec_create(pdev, &drv->encode, ENCODE);
	if (ret)
		goto out;

	ret = bcm2835_codec_create(pdev, &drv->isp, ISP);
	if (ret)
		goto out;

	platform_set_drvdata(pdev, drv);

	return 0;

out:
	if (drv->encode) {
		bcm2835_codec_destroy(drv->encode);
		drv->encode = NULL;
	}
	if (drv->decode) {
		bcm2835_codec_destroy(drv->decode);
		drv->decode = NULL;
	}
	return ret;
}