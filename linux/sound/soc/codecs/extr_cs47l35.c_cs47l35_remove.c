#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct platform_device {int /*<<< orphan*/  dev; } ;
struct TYPE_3__ {int /*<<< orphan*/  madera; int /*<<< orphan*/ * adsp; } ;
struct cs47l35 {TYPE_1__ core; } ;

/* Variables and functions */
 int CS47L35_NUM_ADSP ; 
 int /*<<< orphan*/  MADERA_IRQ_DSP_IRQ1 ; 
 int /*<<< orphan*/  madera_core_free (TYPE_1__*) ; 
 int /*<<< orphan*/  madera_free_irq (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct cs47l35*) ; 
 int /*<<< orphan*/  madera_free_overheat (TYPE_1__*) ; 
 int /*<<< orphan*/  madera_set_irq_wake (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct cs47l35* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  pm_runtime_disable (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wm_adsp2_remove (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int cs47l35_remove(struct platform_device *pdev)
{
	struct cs47l35 *cs47l35 = platform_get_drvdata(pdev);
	int i;

	pm_runtime_disable(&pdev->dev);

	for (i = 0; i < CS47L35_NUM_ADSP; i++)
		wm_adsp2_remove(&cs47l35->core.adsp[i]);

	madera_set_irq_wake(cs47l35->core.madera, MADERA_IRQ_DSP_IRQ1, 0);
	madera_free_irq(cs47l35->core.madera, MADERA_IRQ_DSP_IRQ1, cs47l35);
	madera_free_overheat(&cs47l35->core);
	madera_core_free(&cs47l35->core);

	return 0;
}