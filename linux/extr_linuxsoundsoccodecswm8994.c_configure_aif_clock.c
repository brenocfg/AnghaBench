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
struct wm8994_priv {int* sysclk; int* mclk; int* aifclk; TYPE_1__* fll; } ;
struct snd_soc_component {int /*<<< orphan*/  dev; } ;
struct TYPE_2__ {int out; } ;

/* Variables and functions */
 int EINVAL ; 
 int WM8994_AIF1CLK_DIV ; 
 int WM8994_AIF1CLK_SRC_MASK ; 
 scalar_t__ WM8994_AIF1_CLOCKING_1 ; 
#define  WM8994_SYSCLK_FLL1 131 
#define  WM8994_SYSCLK_FLL2 130 
#define  WM8994_SYSCLK_MCLK1 129 
#define  WM8994_SYSCLK_MCLK2 128 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int,int) ; 
 struct wm8994_priv* snd_soc_component_get_drvdata (struct snd_soc_component*) ; 
 int /*<<< orphan*/  snd_soc_component_update_bits (struct snd_soc_component*,scalar_t__,int,int) ; 

__attribute__((used)) static int configure_aif_clock(struct snd_soc_component *component, int aif)
{
	struct wm8994_priv *wm8994 = snd_soc_component_get_drvdata(component);
	int rate;
	int reg1 = 0;
	int offset;

	if (aif)
		offset = 4;
	else
		offset = 0;

	switch (wm8994->sysclk[aif]) {
	case WM8994_SYSCLK_MCLK1:
		rate = wm8994->mclk[0];
		break;

	case WM8994_SYSCLK_MCLK2:
		reg1 |= 0x8;
		rate = wm8994->mclk[1];
		break;

	case WM8994_SYSCLK_FLL1:
		reg1 |= 0x10;
		rate = wm8994->fll[0].out;
		break;

	case WM8994_SYSCLK_FLL2:
		reg1 |= 0x18;
		rate = wm8994->fll[1].out;
		break;

	default:
		return -EINVAL;
	}

	if (rate >= 13500000) {
		rate /= 2;
		reg1 |= WM8994_AIF1CLK_DIV;

		dev_dbg(component->dev, "Dividing AIF%d clock to %dHz\n",
			aif + 1, rate);
	}

	wm8994->aifclk[aif] = rate;

	snd_soc_component_update_bits(component, WM8994_AIF1_CLOCKING_1 + offset,
			    WM8994_AIF1CLK_SRC_MASK | WM8994_AIF1CLK_DIV,
			    reg1);

	return 0;
}