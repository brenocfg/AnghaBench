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
struct snd_usb_audio {int dummy; } ;
struct audioformat {int rates; int rate_min; int rate_max; unsigned int* rate_table; } ;

/* Variables and functions */
 int MAX_NR_RATES ; 
 int SNDRV_PCM_RATE_CONTINUOUS ; 
 int combine_quad (unsigned char const*) ; 
 int snd_pcm_rate_to_rate_bit (unsigned int) ; 
 int /*<<< orphan*/  usb_audio_err (struct snd_usb_audio*,char*) ; 

__attribute__((used)) static int parse_uac2_sample_rate_range(struct snd_usb_audio *chip,
					struct audioformat *fp, int nr_triplets,
					const unsigned char *data)
{
	int i, nr_rates = 0;

	fp->rates = fp->rate_min = fp->rate_max = 0;

	for (i = 0; i < nr_triplets; i++) {
		int min = combine_quad(&data[2 + 12 * i]);
		int max = combine_quad(&data[6 + 12 * i]);
		int res = combine_quad(&data[10 + 12 * i]);
		unsigned int rate;

		if ((max < 0) || (min < 0) || (res < 0) || (max < min))
			continue;

		/*
		 * for ranges with res == 1, we announce a continuous sample
		 * rate range, and this function should return 0 for no further
		 * parsing.
		 */
		if (res == 1) {
			fp->rate_min = min;
			fp->rate_max = max;
			fp->rates = SNDRV_PCM_RATE_CONTINUOUS;
			return 0;
		}

		for (rate = min; rate <= max; rate += res) {
			if (fp->rate_table)
				fp->rate_table[nr_rates] = rate;
			if (!fp->rate_min || rate < fp->rate_min)
				fp->rate_min = rate;
			if (!fp->rate_max || rate > fp->rate_max)
				fp->rate_max = rate;
			fp->rates |= snd_pcm_rate_to_rate_bit(rate);

			nr_rates++;
			if (nr_rates >= MAX_NR_RATES) {
				usb_audio_err(chip, "invalid uac2 rates\n");
				break;
			}

			/* avoid endless loop */
			if (res == 0)
				break;
		}
	}

	return nr_rates;
}