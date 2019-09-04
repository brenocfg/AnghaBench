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
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int EINVAL ; 
#define  WM8741_DIFF_MODE_MONO_LEFT 131 
#define  WM8741_DIFF_MODE_MONO_RIGHT 130 
#define  WM8741_DIFF_MODE_STEREO 129 
#define  WM8741_DIFF_MODE_STEREO_REVERSED 128 
 int /*<<< orphan*/  snd_soc_add_component_controls (struct snd_soc_component*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct wm8741_priv* snd_soc_component_get_drvdata (struct snd_soc_component*) ; 
 int /*<<< orphan*/  wm8741_snd_controls_mono_left ; 
 int /*<<< orphan*/  wm8741_snd_controls_mono_right ; 
 int /*<<< orphan*/  wm8741_snd_controls_stereo ; 

__attribute__((used)) static int wm8741_add_controls(struct snd_soc_component *component)
{
	struct wm8741_priv *wm8741 = snd_soc_component_get_drvdata(component);

	switch (wm8741->pdata.diff_mode) {
	case WM8741_DIFF_MODE_STEREO:
	case WM8741_DIFF_MODE_STEREO_REVERSED:
		snd_soc_add_component_controls(component,
				wm8741_snd_controls_stereo,
				ARRAY_SIZE(wm8741_snd_controls_stereo));
		break;
	case WM8741_DIFF_MODE_MONO_LEFT:
		snd_soc_add_component_controls(component,
				wm8741_snd_controls_mono_left,
				ARRAY_SIZE(wm8741_snd_controls_mono_left));
		break;
	case WM8741_DIFF_MODE_MONO_RIGHT:
		snd_soc_add_component_controls(component,
				wm8741_snd_controls_mono_right,
				ARRAY_SIZE(wm8741_snd_controls_mono_right));
		break;
	default:
		return -EINVAL;
	}

	return 0;
}