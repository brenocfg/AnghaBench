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
struct snd_sh_dac {TYPE_1__* pdata; int /*<<< orphan*/ * substream; } ;
struct snd_pcm_substream {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* stop ) (TYPE_1__*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  dac_audio_stop_timer (struct snd_sh_dac*) ; 
 struct snd_sh_dac* snd_pcm_substream_chip (struct snd_pcm_substream*) ; 
 int /*<<< orphan*/  stub1 (TYPE_1__*) ; 

__attribute__((used)) static int snd_sh_dac_pcm_close(struct snd_pcm_substream *substream)
{
	struct snd_sh_dac *chip = snd_pcm_substream_chip(substream);

	chip->substream = NULL;

	dac_audio_stop_timer(chip);
	chip->pdata->stop(chip->pdata);

	return 0;
}