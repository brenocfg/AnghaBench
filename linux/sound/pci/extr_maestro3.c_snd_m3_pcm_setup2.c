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
typedef  int u32 ;
struct snd_pcm_runtime {int channels; int rate; int /*<<< orphan*/  format; } ;
struct snd_m3 {int dummy; } ;
struct TYPE_2__ {int data; } ;
struct m3_dma {int in_lists; TYPE_1__ inst; int /*<<< orphan*/ * index_list; void** index; } ;

/* Variables and functions */
 scalar_t__ CDATA_FREQUENCY ; 
 int DP_SHIFT_COUNT ; 
 int /*<<< orphan*/  MEMTYPE_INTERNAL_DATA ; 
 scalar_t__ SRC3_DIRECTION_OFFSET ; 
 void* snd_m3_add_list (struct snd_m3*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  snd_m3_assp_write (struct snd_m3*,int /*<<< orphan*/ ,scalar_t__,int) ; 
 int snd_pcm_format_width (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void snd_m3_pcm_setup2(struct snd_m3 *chip, struct m3_dma *s,
			      struct snd_pcm_runtime *runtime)
{
	u32 freq;

	/* 
	 * put us in the lists if we're not already there
	 */
	if (! s->in_lists) {
		s->index[0] = snd_m3_add_list(chip, s->index_list[0],
					      s->inst.data >> DP_SHIFT_COUNT);
		s->index[1] = snd_m3_add_list(chip, s->index_list[1],
					      s->inst.data >> DP_SHIFT_COUNT);
		s->index[2] = snd_m3_add_list(chip, s->index_list[2],
					      s->inst.data >> DP_SHIFT_COUNT);
		s->in_lists = 1;
	}

	/* write to 'mono' word */
	snd_m3_assp_write(chip, MEMTYPE_INTERNAL_DATA,
			  s->inst.data + SRC3_DIRECTION_OFFSET + 1, 
			  runtime->channels == 2 ? 0 : 1);
	/* write to '8bit' word */
	snd_m3_assp_write(chip, MEMTYPE_INTERNAL_DATA,
			  s->inst.data + SRC3_DIRECTION_OFFSET + 2, 
			  snd_pcm_format_width(runtime->format) == 16 ? 0 : 1);

	/* set up dac/adc rate */
	freq = ((runtime->rate << 15) + 24000 ) / 48000;
	if (freq) 
		freq--;

	snd_m3_assp_write(chip, MEMTYPE_INTERNAL_DATA,
			  s->inst.data + CDATA_FREQUENCY,
			  freq);
}