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
struct snd_es1688 {int dummy; } ;
struct TYPE_2__ {scalar_t__ num; } ;

/* Variables and functions */
 TYPE_1__* clocks ; 
 int /*<<< orphan*/  snd_es1688_write (struct snd_es1688*,int,unsigned int) ; 

__attribute__((used)) static void snd_es1688_set_rate(struct snd_es1688 *chip, struct snd_pcm_substream *substream)
{
	struct snd_pcm_runtime *runtime = substream->runtime;
	unsigned int bits, divider;

	if (runtime->rate_num == clocks[0].num)
		bits = 256 - runtime->rate_den;
	else
		bits = 128 - runtime->rate_den;
	/* set filter register */
	divider = 256 - 7160000*20/(8*82*runtime->rate);
	/* write result to hardware */
	snd_es1688_write(chip, 0xa1, bits);
	snd_es1688_write(chip, 0xa2, divider);
}