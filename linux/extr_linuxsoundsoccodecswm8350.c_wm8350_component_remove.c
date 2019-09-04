#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  work; int /*<<< orphan*/ * jack; } ;
struct TYPE_5__ {int /*<<< orphan*/  work; int /*<<< orphan*/ * jack; } ;
struct TYPE_4__ {int /*<<< orphan*/ * jack; } ;
struct wm8350_data {int /*<<< orphan*/  pga_work; TYPE_3__ hpr; TYPE_2__ hpl; TYPE_1__ mic; } ;
struct wm8350 {int dummy; } ;
struct snd_soc_component {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int WM8350_CODEC_ENA ; 
 int /*<<< orphan*/  WM8350_IRQ_CODEC_JCK_DET_L ; 
 int /*<<< orphan*/  WM8350_IRQ_CODEC_JCK_DET_R ; 
 int /*<<< orphan*/  WM8350_IRQ_CODEC_MICD ; 
 int /*<<< orphan*/  WM8350_IRQ_CODEC_MICSCD ; 
 int /*<<< orphan*/  WM8350_JACK_DETECT ; 
 int WM8350_JDL_ENA ; 
 int WM8350_JDR_ENA ; 
 int /*<<< orphan*/  WM8350_POWER_MGMT_4 ; 
 int /*<<< orphan*/  WM8350_POWER_MGMT_5 ; 
 int WM8350_TOCLK_ENA ; 
 int /*<<< orphan*/  cancel_delayed_work_sync (int /*<<< orphan*/ *) ; 
 struct wm8350* dev_get_platdata (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  flush_delayed_work (int /*<<< orphan*/ *) ; 
 struct wm8350_data* snd_soc_component_get_drvdata (struct snd_soc_component*) ; 
 int /*<<< orphan*/  wm8350_clear_bits (struct wm8350*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  wm8350_free_irq (struct wm8350*,int /*<<< orphan*/ ,struct wm8350_data*) ; 

__attribute__((used)) static void wm8350_component_remove(struct snd_soc_component *component)
{
	struct wm8350_data *priv = snd_soc_component_get_drvdata(component);
	struct wm8350 *wm8350 = dev_get_platdata(component->dev);

	wm8350_clear_bits(wm8350, WM8350_JACK_DETECT,
			  WM8350_JDL_ENA | WM8350_JDR_ENA);
	wm8350_clear_bits(wm8350, WM8350_POWER_MGMT_4, WM8350_TOCLK_ENA);

	wm8350_free_irq(wm8350, WM8350_IRQ_CODEC_MICD, priv);
	wm8350_free_irq(wm8350, WM8350_IRQ_CODEC_MICSCD, priv);
	wm8350_free_irq(wm8350, WM8350_IRQ_CODEC_JCK_DET_L, priv);
	wm8350_free_irq(wm8350, WM8350_IRQ_CODEC_JCK_DET_R, priv);

	priv->hpl.jack = NULL;
	priv->hpr.jack = NULL;
	priv->mic.jack = NULL;

	cancel_delayed_work_sync(&priv->hpl.work);
	cancel_delayed_work_sync(&priv->hpr.work);

	/* if there was any work waiting then we run it now and
	 * wait for its completion */
	flush_delayed_work(&priv->pga_work);

	wm8350_clear_bits(wm8350, WM8350_POWER_MGMT_5, WM8350_CODEC_ENA);
}