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
struct ep93xx_ac97_info {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  AC97GCR ; 
 int /*<<< orphan*/ * ep93xx_ac97_info ; 
 int /*<<< orphan*/  ep93xx_ac97_write_reg (struct ep93xx_ac97_info*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct ep93xx_ac97_info* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  snd_soc_set_ac97_ops (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  snd_soc_unregister_component (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int ep93xx_ac97_remove(struct platform_device *pdev)
{
	struct ep93xx_ac97_info	*info = platform_get_drvdata(pdev);

	snd_soc_unregister_component(&pdev->dev);

	/* disable the AC97 controller */
	ep93xx_ac97_write_reg(info, AC97GCR, 0);

	ep93xx_ac97_info = NULL;

	snd_soc_set_ac97_ops(NULL);

	return 0;
}