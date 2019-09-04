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
struct TYPE_2__ {int irq_flags; scalar_t__ num_retune_mobile_cfgs; } ;
struct wm8996_priv {TYPE_1__ pdata; int /*<<< orphan*/  fll_lock; int /*<<< orphan*/  dcs_done; struct snd_soc_component* component; } ;
struct snd_soc_component {int /*<<< orphan*/  dev; } ;
struct i2c_client {scalar_t__ irq; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int IRQF_ONESHOT ; 
 int IRQF_TRIGGER_FALLING ; 
 int IRQF_TRIGGER_LOW ; 
 int IRQF_TRIGGER_RISING ; 
 int WM8996_IM_DCS_DONE_01_EINT ; 
 int WM8996_IM_DCS_DONE_23_EINT ; 
 int WM8996_IM_FIFOS_ERR_EINT ; 
 int WM8996_IM_FLL_LOCK_EINT ; 
 int WM8996_IM_IRQ ; 
 int /*<<< orphan*/  WM8996_INTERRUPT_CONTROL ; 
 int /*<<< orphan*/  WM8996_INTERRUPT_STATUS_2_MASK ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  init_completion (int /*<<< orphan*/ *) ; 
 int request_threaded_irq (scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,char*,struct snd_soc_component*) ; 
 int /*<<< orphan*/  snd_soc_add_component_controls (struct snd_soc_component*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct wm8996_priv* snd_soc_component_get_drvdata (struct snd_soc_component*) ; 
 int /*<<< orphan*/  snd_soc_component_update_bits (struct snd_soc_component*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 struct i2c_client* to_i2c_client (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wm8996_edge_irq ; 
 int /*<<< orphan*/  wm8996_eq_controls ; 
 int /*<<< orphan*/  wm8996_irq ; 
 int /*<<< orphan*/  wm8996_retune_mobile_pdata (struct snd_soc_component*) ; 

__attribute__((used)) static int wm8996_probe(struct snd_soc_component *component)
{
	int ret;
	struct wm8996_priv *wm8996 = snd_soc_component_get_drvdata(component);
	struct i2c_client *i2c = to_i2c_client(component->dev);
	int irq_flags;

	wm8996->component = component;

	init_completion(&wm8996->dcs_done);
	init_completion(&wm8996->fll_lock);

	if (wm8996->pdata.num_retune_mobile_cfgs)
		wm8996_retune_mobile_pdata(component);
	else
		snd_soc_add_component_controls(component, wm8996_eq_controls,
				     ARRAY_SIZE(wm8996_eq_controls));

	if (i2c->irq) {
		if (wm8996->pdata.irq_flags)
			irq_flags = wm8996->pdata.irq_flags;
		else
			irq_flags = IRQF_TRIGGER_LOW;

		irq_flags |= IRQF_ONESHOT;

		if (irq_flags & (IRQF_TRIGGER_RISING | IRQF_TRIGGER_FALLING))
			ret = request_threaded_irq(i2c->irq, NULL,
						   wm8996_edge_irq,
						   irq_flags, "wm8996", component);
		else
			ret = request_threaded_irq(i2c->irq, NULL, wm8996_irq,
						   irq_flags, "wm8996", component);

		if (ret == 0) {
			/* Unmask the interrupt */
			snd_soc_component_update_bits(component, WM8996_INTERRUPT_CONTROL,
					    WM8996_IM_IRQ, 0);

			/* Enable error reporting and DC servo status */
			snd_soc_component_update_bits(component,
					    WM8996_INTERRUPT_STATUS_2_MASK,
					    WM8996_IM_DCS_DONE_23_EINT |
					    WM8996_IM_DCS_DONE_01_EINT |
					    WM8996_IM_FLL_LOCK_EINT |
					    WM8996_IM_FIFOS_ERR_EINT,
					    0);
		} else {
			dev_err(component->dev, "Failed to request IRQ: %d\n",
				ret);
			return ret;
		}
	}

	return 0;
}