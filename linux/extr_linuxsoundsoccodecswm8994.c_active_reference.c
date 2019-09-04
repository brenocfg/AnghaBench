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
struct wm8994_priv {int /*<<< orphan*/  accdet_lock; int /*<<< orphan*/  active_refcount; } ;
struct snd_soc_component {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  WM1811_JACKDET_MODE_AUDIO ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct wm8994_priv* snd_soc_component_get_drvdata (struct snd_soc_component*) ; 
 int /*<<< orphan*/  wm1811_jackdet_set_mode (struct snd_soc_component*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void active_reference(struct snd_soc_component *component)
{
	struct wm8994_priv *wm8994 = snd_soc_component_get_drvdata(component);

	mutex_lock(&wm8994->accdet_lock);

	wm8994->active_refcount++;

	dev_dbg(component->dev, "Active refcount incremented, now %d\n",
		wm8994->active_refcount);

	/* If we're using jack detection go into audio mode */
	wm1811_jackdet_set_mode(component, WM1811_JACKDET_MODE_AUDIO);

	mutex_unlock(&wm8994->accdet_lock);
}