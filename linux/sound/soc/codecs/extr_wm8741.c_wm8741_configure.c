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
struct TYPE_2__ {int diff_mode; } ;
struct wm8741_priv {TYPE_1__ pdata; } ;
struct snd_soc_component {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  WM8741_DACLLSB_ATTENUATION ; 
 int /*<<< orphan*/  WM8741_DACLMSB_ATTENUATION ; 
 int /*<<< orphan*/  WM8741_DACRLSB_ATTENUATION ; 
 int /*<<< orphan*/  WM8741_DACRMSB_ATTENUATION ; 
 int WM8741_DIFF_MASK ; 
#define  WM8741_DIFF_MODE_MONO_LEFT 131 
#define  WM8741_DIFF_MODE_MONO_RIGHT 130 
#define  WM8741_DIFF_MODE_STEREO 129 
#define  WM8741_DIFF_MODE_STEREO_REVERSED 128 
 int WM8741_DIFF_SHIFT ; 
 int /*<<< orphan*/  WM8741_MODE_CONTROL_2 ; 
 int WM8741_UPDATELL ; 
 int WM8741_UPDATELM ; 
 int WM8741_UPDATERL ; 
 int WM8741_UPDATERM ; 
 struct wm8741_priv* snd_soc_component_get_drvdata (struct snd_soc_component*) ; 
 int /*<<< orphan*/  snd_soc_component_update_bits (struct snd_soc_component*,int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static int wm8741_configure(struct snd_soc_component *component)
{
	struct wm8741_priv *wm8741 = snd_soc_component_get_drvdata(component);

	/* Configure differential mode */
	switch (wm8741->pdata.diff_mode) {
	case WM8741_DIFF_MODE_STEREO:
	case WM8741_DIFF_MODE_STEREO_REVERSED:
	case WM8741_DIFF_MODE_MONO_LEFT:
	case WM8741_DIFF_MODE_MONO_RIGHT:
		snd_soc_component_update_bits(component, WM8741_MODE_CONTROL_2,
				WM8741_DIFF_MASK,
				wm8741->pdata.diff_mode << WM8741_DIFF_SHIFT);
		break;
	default:
		return -EINVAL;
	}

	/* Change some default settings - latch VU */
	snd_soc_component_update_bits(component, WM8741_DACLLSB_ATTENUATION,
			WM8741_UPDATELL, WM8741_UPDATELL);
	snd_soc_component_update_bits(component, WM8741_DACLMSB_ATTENUATION,
			WM8741_UPDATELM, WM8741_UPDATELM);
	snd_soc_component_update_bits(component, WM8741_DACRLSB_ATTENUATION,
			WM8741_UPDATERL, WM8741_UPDATERL);
	snd_soc_component_update_bits(component, WM8741_DACRMSB_ATTENUATION,
			WM8741_UPDATERM, WM8741_UPDATERM);

	return 0;
}