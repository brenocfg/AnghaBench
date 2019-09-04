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
struct snd_soc_pcm_runtime {struct snd_soc_card* card; } ;
struct snd_soc_card {struct glb_pool* drvdata; } ;
struct glb_pool {int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int __snd_allo_piano_dsp_program (struct snd_soc_pcm_runtime*,unsigned int,unsigned int,unsigned int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int snd_allo_piano_dsp_program(struct snd_soc_pcm_runtime *rtd,
		unsigned int mode, unsigned int rate, unsigned int lowpass)
{
	struct snd_soc_card *card = rtd->card;
	struct glb_pool *glb_ptr = card->drvdata;
	int ret = 0;

	mutex_lock(&glb_ptr->lock);

	ret = __snd_allo_piano_dsp_program(rtd, mode, rate, lowpass);

	mutex_unlock(&glb_ptr->lock);

	return ret;
}