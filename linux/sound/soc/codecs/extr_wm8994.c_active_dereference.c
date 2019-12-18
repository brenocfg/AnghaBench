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
typedef  int /*<<< orphan*/  u16 ;
struct wm8994_priv {scalar_t__ active_refcount; int /*<<< orphan*/  accdet_lock; scalar_t__ mic_detecting; scalar_t__ jack_mic; } ;
struct snd_soc_component {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  WM1811_JACKDET_MODE_JACK ; 
 int /*<<< orphan*/  WM1811_JACKDET_MODE_MIC ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,scalar_t__) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct wm8994_priv* snd_soc_component_get_drvdata (struct snd_soc_component*) ; 
 int /*<<< orphan*/  wm1811_jackdet_set_mode (struct snd_soc_component*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void active_dereference(struct snd_soc_component *component)
{
	struct wm8994_priv *wm8994 = snd_soc_component_get_drvdata(component);
	u16 mode;

	mutex_lock(&wm8994->accdet_lock);

	wm8994->active_refcount--;

	dev_dbg(component->dev, "Active refcount decremented, now %d\n",
		wm8994->active_refcount);

	if (wm8994->active_refcount == 0) {
		/* Go into appropriate detection only mode */
		if (wm8994->jack_mic || wm8994->mic_detecting)
			mode = WM1811_JACKDET_MODE_MIC;
		else
			mode = WM1811_JACKDET_MODE_JACK;

		wm1811_jackdet_set_mode(component, mode);
	}

	mutex_unlock(&wm8994->accdet_lock);
}