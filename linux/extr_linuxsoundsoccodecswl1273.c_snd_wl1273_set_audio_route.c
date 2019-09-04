#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct wl1273_priv {scalar_t__ mode; } ;
struct snd_soc_component {int dummy; } ;
struct snd_kcontrol {int dummy; } ;
struct TYPE_3__ {scalar_t__* item; } ;
struct TYPE_4__ {TYPE_1__ enumerated; } ;
struct snd_ctl_elem_value {TYPE_2__ value; } ;

/* Variables and functions */
 scalar_t__ ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int EINVAL ; 
 int EPERM ; 
 struct wl1273_priv* snd_soc_component_get_drvdata (struct snd_soc_component*) ; 
 scalar_t__ snd_soc_component_is_active (struct snd_soc_component*) ; 
 struct snd_soc_component* snd_soc_kcontrol_component (struct snd_kcontrol*) ; 
 int /*<<< orphan*/  wl1273_audio_route ; 

__attribute__((used)) static int snd_wl1273_set_audio_route(struct snd_kcontrol *kcontrol,
				      struct snd_ctl_elem_value *ucontrol)
{
	struct snd_soc_component *component = snd_soc_kcontrol_component(kcontrol);
	struct wl1273_priv *wl1273 = snd_soc_component_get_drvdata(component);

	if (wl1273->mode == ucontrol->value.enumerated.item[0])
		return 0;

	/* Do not allow changes while stream is running */
	if (snd_soc_component_is_active(component))
		return -EPERM;

	if (ucontrol->value.enumerated.item[0] >=  ARRAY_SIZE(wl1273_audio_route))
		return -EINVAL;

	wl1273->mode = ucontrol->value.enumerated.item[0];

	return 1;
}