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
struct wcd9335_codec {int /*<<< orphan*/  irq_data; int /*<<< orphan*/  clsh_ctrl; } ;
struct snd_soc_component {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  WCD9335_IRQ_SLIMBUS ; 
 struct wcd9335_codec* dev_get_drvdata (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,struct wcd9335_codec*) ; 
 int /*<<< orphan*/  regmap_irq_get_virq (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wcd_clsh_ctrl_free (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void wcd9335_codec_remove(struct snd_soc_component *comp)
{
	struct wcd9335_codec *wcd = dev_get_drvdata(comp->dev);

	wcd_clsh_ctrl_free(wcd->clsh_ctrl);
	free_irq(regmap_irq_get_virq(wcd->irq_data, WCD9335_IRQ_SLIMBUS), wcd);
}