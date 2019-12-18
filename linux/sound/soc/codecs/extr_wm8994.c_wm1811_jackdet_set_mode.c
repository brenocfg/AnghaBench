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
typedef  scalar_t__ u16 ;
struct wm8994_priv {scalar_t__ jackdet_mode; scalar_t__ active_refcount; TYPE_1__* micdet; int /*<<< orphan*/  jackdet; } ;
struct snd_soc_component {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  jack; } ;

/* Variables and functions */
 scalar_t__ WM1811_JACKDET_MODE_AUDIO ; 
 int /*<<< orphan*/  WM1811_JACKDET_MODE_MASK ; 
 scalar_t__ WM1811_JACKDET_MODE_NONE ; 
 int /*<<< orphan*/  WM8994_ANTIPOP_2 ; 
 struct wm8994_priv* snd_soc_component_get_drvdata (struct snd_soc_component*) ; 
 int /*<<< orphan*/  snd_soc_component_update_bits (struct snd_soc_component*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void wm1811_jackdet_set_mode(struct snd_soc_component *component, u16 mode)
{
	struct wm8994_priv *wm8994 = snd_soc_component_get_drvdata(component);

	if (!wm8994->jackdet || !wm8994->micdet[0].jack)
		return;

	if (wm8994->active_refcount)
		mode = WM1811_JACKDET_MODE_AUDIO;

	if (mode == wm8994->jackdet_mode)
		return;

	wm8994->jackdet_mode = mode;

	/* Always use audio mode to detect while the system is active */
	if (mode != WM1811_JACKDET_MODE_NONE)
		mode = WM1811_JACKDET_MODE_AUDIO;

	snd_soc_component_update_bits(component, WM8994_ANTIPOP_2,
			    WM1811_JACKDET_MODE_MASK, mode);
}