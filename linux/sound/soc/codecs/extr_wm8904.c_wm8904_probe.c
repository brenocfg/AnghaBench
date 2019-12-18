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
struct wm8904_priv {int devtype; } ;
struct snd_soc_component {int /*<<< orphan*/  dev; } ;
struct TYPE_2__ {int /*<<< orphan*/  capture; } ;

/* Variables and functions */
 int EINVAL ; 
#define  WM8904 129 
#define  WM8912 128 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 struct wm8904_priv* snd_soc_component_get_drvdata (struct snd_soc_component*) ; 
 int /*<<< orphan*/  wm8904_add_widgets (struct snd_soc_component*) ; 
 TYPE_1__ wm8904_dai ; 
 int /*<<< orphan*/  wm8904_handle_pdata (struct snd_soc_component*) ; 

__attribute__((used)) static int wm8904_probe(struct snd_soc_component *component)
{
	struct wm8904_priv *wm8904 = snd_soc_component_get_drvdata(component);

	switch (wm8904->devtype) {
	case WM8904:
		break;
	case WM8912:
		memset(&wm8904_dai.capture, 0, sizeof(wm8904_dai.capture));
		break;
	default:
		dev_err(component->dev, "Unknown device type %d\n",
			wm8904->devtype);
		return -EINVAL;
	}

	wm8904_handle_pdata(component);

	wm8904_add_widgets(component);

	return 0;
}