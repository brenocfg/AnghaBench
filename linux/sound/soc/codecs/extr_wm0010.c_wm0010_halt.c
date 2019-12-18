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
struct wm0010_priv {int state; int /*<<< orphan*/  irq_lock; int /*<<< orphan*/  core_supplies; int /*<<< orphan*/  dbvdd; int /*<<< orphan*/  gpio_reset_value; int /*<<< orphan*/  gpio_reset; } ;
struct snd_soc_component {int dummy; } ;
typedef  enum wm0010_state { ____Placeholder_wm0010_state } wm0010_state ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
#define  WM0010_BOOTROM 132 
#define  WM0010_FIRMWARE 131 
#define  WM0010_OUT_OF_RESET 130 
#define  WM0010_POWER_OFF 129 
#define  WM0010_STAGE2 128 
 int /*<<< orphan*/  gpio_set_value_cansleep (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  regulator_bulk_disable (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  regulator_disable (int /*<<< orphan*/ ) ; 
 struct wm0010_priv* snd_soc_component_get_drvdata (struct snd_soc_component*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void wm0010_halt(struct snd_soc_component *component)
{
	struct wm0010_priv *wm0010 = snd_soc_component_get_drvdata(component);
	unsigned long flags;
	enum wm0010_state state;

	/* Fetch the wm0010 state */
	spin_lock_irqsave(&wm0010->irq_lock, flags);
	state = wm0010->state;
	spin_unlock_irqrestore(&wm0010->irq_lock, flags);

	switch (state) {
	case WM0010_POWER_OFF:
		/* If there's nothing to do, bail out */
		return;
	case WM0010_OUT_OF_RESET:
	case WM0010_BOOTROM:
	case WM0010_STAGE2:
	case WM0010_FIRMWARE:
		/* Remember to put chip back into reset */
		gpio_set_value_cansleep(wm0010->gpio_reset,
					wm0010->gpio_reset_value);
		/* Disable the regulators */
		regulator_disable(wm0010->dbvdd);
		regulator_bulk_disable(ARRAY_SIZE(wm0010->core_supplies),
				       wm0010->core_supplies);
		break;
	}

	spin_lock_irqsave(&wm0010->irq_lock, flags);
	wm0010->state = WM0010_POWER_OFF;
	spin_unlock_irqrestore(&wm0010->irq_lock, flags);
}