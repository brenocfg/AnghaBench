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

/* Variables and functions */
 int /*<<< orphan*/  snd_dmaengine_pcm_unregister (int /*<<< orphan*/ *) ; 

int ux500_pcm_unregister_platform(struct platform_device *pdev)
{
	snd_dmaengine_pcm_unregister(&pdev->dev);
	return 0;
}