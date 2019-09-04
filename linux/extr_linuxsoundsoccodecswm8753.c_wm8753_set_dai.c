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
typedef  int u16 ;
struct wm8753_priv {int dai_func; int /*<<< orphan*/  voice_fmt; int /*<<< orphan*/  hifi_fmt; } ;
struct snd_soc_component {int dummy; } ;
struct snd_kcontrol {int dummy; } ;
struct TYPE_3__ {int* item; } ;
struct TYPE_4__ {TYPE_1__ enumerated; } ;
struct snd_ctl_elem_value {TYPE_2__ value; } ;

/* Variables and functions */
 int EBUSY ; 
 int /*<<< orphan*/  WM8753_IOCTL ; 
 struct wm8753_priv* snd_soc_component_get_drvdata (struct snd_soc_component*) ; 
 scalar_t__ snd_soc_component_is_active (struct snd_soc_component*) ; 
 int snd_soc_component_read32 (struct snd_soc_component*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_soc_component_write (struct snd_soc_component*,int /*<<< orphan*/ ,int) ; 
 struct snd_soc_component* snd_soc_kcontrol_component (struct snd_kcontrol*) ; 
 int /*<<< orphan*/  wm8753_hifi_write_dai_fmt (struct snd_soc_component*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wm8753_voice_write_dai_fmt (struct snd_soc_component*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int wm8753_set_dai(struct snd_kcontrol *kcontrol,
	struct snd_ctl_elem_value *ucontrol)
{
	struct snd_soc_component *component = snd_soc_kcontrol_component(kcontrol);
	struct wm8753_priv *wm8753 = snd_soc_component_get_drvdata(component);
	u16 ioctl;

	if (wm8753->dai_func == ucontrol->value.enumerated.item[0])
		return 0;

	if (snd_soc_component_is_active(component))
		return -EBUSY;

	ioctl = snd_soc_component_read32(component, WM8753_IOCTL);

	wm8753->dai_func = ucontrol->value.enumerated.item[0];

	if (((ioctl >> 2) & 0x3) == wm8753->dai_func)
		return 1;

	ioctl = (ioctl & 0x1f3) | (wm8753->dai_func << 2);
	snd_soc_component_write(component, WM8753_IOCTL, ioctl);


	wm8753_hifi_write_dai_fmt(component, wm8753->hifi_fmt);
	wm8753_voice_write_dai_fmt(component, wm8753->voice_fmt);

	return 1;
}