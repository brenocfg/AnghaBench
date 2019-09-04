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
struct platform_device {int dummy; } ;
struct bcm2835_codec_driver {int /*<<< orphan*/  decode; int /*<<< orphan*/  encode; int /*<<< orphan*/  isp; } ;

/* Variables and functions */
 int /*<<< orphan*/  bcm2835_codec_destroy (int /*<<< orphan*/ ) ; 
 struct bcm2835_codec_driver* platform_get_drvdata (struct platform_device*) ; 

__attribute__((used)) static int bcm2835_codec_remove(struct platform_device *pdev)
{
	struct bcm2835_codec_driver *drv = platform_get_drvdata(pdev);

	bcm2835_codec_destroy(drv->isp);

	bcm2835_codec_destroy(drv->encode);

	bcm2835_codec_destroy(drv->decode);

	return 0;
}