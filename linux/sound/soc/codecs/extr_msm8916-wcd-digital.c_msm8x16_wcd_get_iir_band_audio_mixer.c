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
typedef  int /*<<< orphan*/  u32 ;
struct soc_bytes_ext {int /*<<< orphan*/  max; } ;
struct wcd_iir_filter_ctl {int iir_idx; int band_idx; struct soc_bytes_ext bytes_ext; } ;
struct snd_soc_component {int dummy; } ;
struct snd_kcontrol {scalar_t__ private_value; } ;
struct TYPE_3__ {int /*<<< orphan*/  data; } ;
struct TYPE_4__ {TYPE_1__ bytes; } ;
struct snd_ctl_elem_value {TYPE_2__ value; } ;

/* Variables and functions */
 int BAND_MAX ; 
 int /*<<< orphan*/  get_iir_band_coeff (struct snd_soc_component*,int,int,int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct snd_soc_component* snd_soc_kcontrol_component (struct snd_kcontrol*) ; 

__attribute__((used)) static int msm8x16_wcd_get_iir_band_audio_mixer(
					struct snd_kcontrol *kcontrol,
					struct snd_ctl_elem_value *ucontrol)
{

	struct snd_soc_component *component =
			snd_soc_kcontrol_component(kcontrol);
	struct wcd_iir_filter_ctl *ctl =
			(struct wcd_iir_filter_ctl *)kcontrol->private_value;
	struct soc_bytes_ext *params = &ctl->bytes_ext;
	int iir_idx = ctl->iir_idx;
	int band_idx = ctl->band_idx;
	u32 coeff[BAND_MAX];

	coeff[0] = get_iir_band_coeff(component, iir_idx, band_idx, 0);
	coeff[1] = get_iir_band_coeff(component, iir_idx, band_idx, 1);
	coeff[2] = get_iir_band_coeff(component, iir_idx, band_idx, 2);
	coeff[3] = get_iir_band_coeff(component, iir_idx, band_idx, 3);
	coeff[4] = get_iir_band_coeff(component, iir_idx, band_idx, 4);

	memcpy(ucontrol->value.bytes.data, &coeff[0], params->max);

	return 0;
}