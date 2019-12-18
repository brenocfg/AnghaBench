#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/ * adsp; struct arizona* arizona; } ;
struct wm5102_priv {TYPE_1__ core; } ;
struct platform_device {int /*<<< orphan*/  dev; } ;
struct arizona {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARIZONA_IRQ_DSP_IRQ1 ; 
 int /*<<< orphan*/  arizona_free_irq (struct arizona*,int /*<<< orphan*/ ,struct wm5102_priv*) ; 
 int /*<<< orphan*/  arizona_free_spk_irqs (struct arizona*) ; 
 int /*<<< orphan*/  arizona_set_irq_wake (struct arizona*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct wm5102_priv* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  pm_runtime_disable (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wm_adsp2_remove (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int wm5102_remove(struct platform_device *pdev)
{
	struct wm5102_priv *wm5102 = platform_get_drvdata(pdev);
	struct arizona *arizona = wm5102->core.arizona;

	pm_runtime_disable(&pdev->dev);

	wm_adsp2_remove(&wm5102->core.adsp[0]);

	arizona_free_spk_irqs(arizona);

	arizona_set_irq_wake(arizona, ARIZONA_IRQ_DSP_IRQ1, 0);
	arizona_free_irq(arizona, ARIZONA_IRQ_DSP_IRQ1, wm5102);

	return 0;
}