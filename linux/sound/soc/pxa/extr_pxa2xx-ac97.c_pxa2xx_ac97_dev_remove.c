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
struct ac97_controller {int dummy; } ;

/* Variables and functions */
 struct ac97_controller* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  pxa2xx_ac97_hw_remove (struct platform_device*) ; 
 int /*<<< orphan*/  snd_ac97_controller_unregister (struct ac97_controller*) ; 

__attribute__((used)) static int pxa2xx_ac97_dev_remove(struct platform_device *pdev)
{
	struct ac97_controller *ctrl = platform_get_drvdata(pdev);

	snd_ac97_controller_unregister(ctrl);
	pxa2xx_ac97_hw_remove(pdev);
	return 0;
}