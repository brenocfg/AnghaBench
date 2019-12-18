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
typedef  int /*<<< orphan*/  uint32_t ;
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
 scalar_t__ LPASS_CDC_IIR1_COEF_B1_CTL ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_iir_band_coeff (struct snd_soc_component*,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_soc_component_write (struct snd_soc_component*,scalar_t__,int) ; 
 struct snd_soc_component* snd_soc_kcontrol_component (struct snd_kcontrol*) ; 

__attribute__((used)) static int msm8x16_wcd_put_iir_band_audio_mixer(
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

	memcpy(&coeff[0], ucontrol->value.bytes.data, params->max);

	/* Mask top bit it is reserved */
	/* Updates addr automatically for each B2 write */
	snd_soc_component_write(component,
		(LPASS_CDC_IIR1_COEF_B1_CTL + 64 * iir_idx),
		(band_idx * BAND_MAX * sizeof(uint32_t)) & 0x7F);

	set_iir_band_coeff(component, iir_idx, band_idx, coeff[0]);
	set_iir_band_coeff(component, iir_idx, band_idx, coeff[1]);
	set_iir_band_coeff(component, iir_idx, band_idx, coeff[2]);
	set_iir_band_coeff(component, iir_idx, band_idx, coeff[3]);
	set_iir_band_coeff(component, iir_idx, band_idx, coeff[4]);

	return 0;
}