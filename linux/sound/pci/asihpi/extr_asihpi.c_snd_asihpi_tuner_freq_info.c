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
typedef  scalar_t__ u32 ;
typedef  int u16 ;
struct snd_kcontrol {scalar_t__ private_value; } ;
struct TYPE_3__ {int min; int max; int step; } ;
struct TYPE_4__ {TYPE_1__ integer; } ;
struct snd_ctl_elem_info {int count; TYPE_2__ value; int /*<<< orphan*/  type; } ;

/* Variables and functions */
 int HPI_TUNER_BAND_LAST ; 
 scalar_t__ INT_MAX ; 
 int /*<<< orphan*/  SNDRV_CTL_ELEM_TYPE_INTEGER ; 
 int asihpi_tuner_band_query (struct snd_kcontrol*,int*,int) ; 
 int hpi_tuner_query_frequency (scalar_t__,int,int,scalar_t__*) ; 

__attribute__((used)) static int snd_asihpi_tuner_freq_info(struct snd_kcontrol *kcontrol,
				  struct snd_ctl_elem_info *uinfo)
{
	u32 h_control = kcontrol->private_value;
	u16 err;
	u16 tuner_bands[HPI_TUNER_BAND_LAST];
	u16 num_bands = 0, band_iter, idx;
	u32 freq_range[3], temp_freq_range[3];

	num_bands = asihpi_tuner_band_query(kcontrol, tuner_bands,
			HPI_TUNER_BAND_LAST);

	freq_range[0] = INT_MAX;
	freq_range[1] = 0;
	freq_range[2] = INT_MAX;

	for (band_iter = 0; band_iter < num_bands; band_iter++) {
		for (idx = 0; idx < 3; idx++) {
			err = hpi_tuner_query_frequency(h_control,
				idx, tuner_bands[band_iter],
				&temp_freq_range[idx]);
			if (err != 0)
				return err;
		}

		/* skip band with bogus stepping */
		if (temp_freq_range[2] <= 0)
			continue;

		if (temp_freq_range[0] < freq_range[0])
			freq_range[0] = temp_freq_range[0];
		if (temp_freq_range[1] > freq_range[1])
			freq_range[1] = temp_freq_range[1];
		if (temp_freq_range[2] < freq_range[2])
			freq_range[2] = temp_freq_range[2];
	}

	uinfo->type = SNDRV_CTL_ELEM_TYPE_INTEGER;
	uinfo->count = 1;
	uinfo->value.integer.min = ((int)freq_range[0]);
	uinfo->value.integer.max = ((int)freq_range[1]);
	uinfo->value.integer.step = ((int)freq_range[2]);
	return 0;
}