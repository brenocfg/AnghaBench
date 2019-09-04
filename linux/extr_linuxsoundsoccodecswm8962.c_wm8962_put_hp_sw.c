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
struct snd_soc_component {int dummy; } ;
struct snd_kcontrol {int dummy; } ;
struct snd_ctl_elem_value {int dummy; } ;

/* Variables and functions */
 int WM8962_HPOUTL_PGA_ENA ; 
 int /*<<< orphan*/  WM8962_HPOUTL_VOLUME ; 
 int WM8962_HPOUTR_PGA_ENA ; 
 int /*<<< orphan*/  WM8962_HPOUTR_VOLUME ; 
 int /*<<< orphan*/  WM8962_PWR_MGMT_2 ; 
 int snd_soc_component_read32 (struct snd_soc_component*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_soc_component_write (struct snd_soc_component*,int /*<<< orphan*/ ,int) ; 
 struct snd_soc_component* snd_soc_kcontrol_component (struct snd_kcontrol*) ; 
 int snd_soc_put_volsw (struct snd_kcontrol*,struct snd_ctl_elem_value*) ; 

__attribute__((used)) static int wm8962_put_hp_sw(struct snd_kcontrol *kcontrol,
			    struct snd_ctl_elem_value *ucontrol)
{
	struct snd_soc_component *component = snd_soc_kcontrol_component(kcontrol);
	int ret;

	/* Apply the update (if any) */
        ret = snd_soc_put_volsw(kcontrol, ucontrol);
	if (ret == 0)
		return 0;

	/* If the left PGA is enabled hit that VU bit... */
	ret = snd_soc_component_read32(component, WM8962_PWR_MGMT_2);
	if (ret & WM8962_HPOUTL_PGA_ENA) {
		snd_soc_component_write(component, WM8962_HPOUTL_VOLUME,
			      snd_soc_component_read32(component, WM8962_HPOUTL_VOLUME));
		return 1;
	}

	/* ...otherwise the right.  The VU is stereo. */
	if (ret & WM8962_HPOUTR_PGA_ENA)
		snd_soc_component_write(component, WM8962_HPOUTR_VOLUME,
			      snd_soc_component_read32(component, WM8962_HPOUTR_VOLUME));

	return 1;
}