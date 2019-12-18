#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct platform_device {int /*<<< orphan*/  dev; } ;
struct TYPE_4__ {int /*<<< orphan*/  madera; int /*<<< orphan*/ * adsp; } ;
struct cs47l15 {TYPE_1__ core; } ;

/* Variables and functions */
 int /*<<< orphan*/  MADERA_IRQ_DSP_IRQ1 ; 
 int /*<<< orphan*/  madera_core_free (TYPE_1__*) ; 
 int /*<<< orphan*/  madera_free_bus_error_irq (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  madera_free_irq (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct cs47l15*) ; 
 int /*<<< orphan*/  madera_free_overheat (TYPE_1__*) ; 
 int /*<<< orphan*/  madera_set_irq_wake (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct cs47l15* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  pm_runtime_disable (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wm_adsp2_remove (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int cs47l15_remove(struct platform_device *pdev)
{
	struct cs47l15 *cs47l15 = platform_get_drvdata(pdev);

	pm_runtime_disable(&pdev->dev);

	madera_free_bus_error_irq(&cs47l15->core, 0);

	wm_adsp2_remove(&cs47l15->core.adsp[0]);

	madera_set_irq_wake(cs47l15->core.madera, MADERA_IRQ_DSP_IRQ1, 0);
	madera_free_irq(cs47l15->core.madera, MADERA_IRQ_DSP_IRQ1, cs47l15);
	madera_free_overheat(&cs47l15->core);
	madera_core_free(&cs47l15->core);

	return 0;
}