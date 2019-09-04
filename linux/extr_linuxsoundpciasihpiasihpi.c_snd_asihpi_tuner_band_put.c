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
typedef  int /*<<< orphan*/  u16 ;
struct snd_kcontrol {int /*<<< orphan*/  private_value; } ;
struct TYPE_3__ {unsigned int* item; } ;
struct TYPE_4__ {TYPE_1__ enumerated; } ;
struct snd_ctl_elem_value {TYPE_2__ value; } ;

/* Variables and functions */
 int ARRAY_SIZE (int /*<<< orphan*/ *) ; 
 int HPI_TUNER_BAND_LAST ; 
 int /*<<< orphan*/  asihpi_tuner_band_query (struct snd_kcontrol*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  hpi_handle_error (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hpi_tuner_set_band (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int snd_asihpi_tuner_band_put(struct snd_kcontrol *kcontrol,
				 struct snd_ctl_elem_value *ucontrol)
{
	/*
	struct snd_card_asihpi *asihpi = snd_kcontrol_chip(kcontrol);
	*/
	u32 h_control = kcontrol->private_value;
	unsigned int idx;
	u16 band;
	u16 tuner_bands[HPI_TUNER_BAND_LAST];
	u32 num_bands = 0;

	num_bands = asihpi_tuner_band_query(kcontrol, tuner_bands,
			HPI_TUNER_BAND_LAST);

	idx = ucontrol->value.enumerated.item[0];
	if (idx >= ARRAY_SIZE(tuner_bands))
		idx = ARRAY_SIZE(tuner_bands) - 1;
	band = tuner_bands[idx];
	hpi_handle_error(hpi_tuner_set_band(h_control, band));

	return 1;
}