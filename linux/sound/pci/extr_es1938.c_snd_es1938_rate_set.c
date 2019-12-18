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
struct snd_pcm_substream {struct snd_pcm_runtime* runtime; } ;
struct snd_pcm_runtime {scalar_t__ rate_num; int rate_den; int rate; } ;
struct es1938 {int dummy; } ;
struct TYPE_2__ {scalar_t__ num; } ;

/* Variables and functions */
 int DAC2 ; 
 TYPE_1__* clocks ; 
 int /*<<< orphan*/  snd_es1938_mixer_write (struct es1938*,int,unsigned int) ; 
 int /*<<< orphan*/  snd_es1938_write (struct es1938*,int,unsigned int) ; 

__attribute__((used)) static void snd_es1938_rate_set(struct es1938 *chip, 
				struct snd_pcm_substream *substream,
				int mode)
{
	unsigned int bits, div0;
	struct snd_pcm_runtime *runtime = substream->runtime;
	if (runtime->rate_num == clocks[0].num)
		bits = 128 - runtime->rate_den;
	else
		bits = 256 - runtime->rate_den;

	/* set filter register */
	div0 = 256 - 7160000*20/(8*82*runtime->rate);
		
	if (mode == DAC2) {
		snd_es1938_mixer_write(chip, 0x70, bits);
		snd_es1938_mixer_write(chip, 0x72, div0);
	} else {
		snd_es1938_write(chip, 0xA1, bits);
		snd_es1938_write(chip, 0xA2, div0);
	}
}