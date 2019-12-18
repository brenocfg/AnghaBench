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
struct snd_pcm_substream {int dummy; } ;
struct snd_pcm_indirect2 {int dummy; } ;
struct snd_ml403_ac97cr {struct snd_pcm_indirect2 capture_ind2_rec; struct snd_pcm_substream* capture_substream; struct snd_pcm_indirect2 ind_rec; struct snd_pcm_substream* playback_substream; } ;
typedef  int /*<<< orphan*/  snd_pcm_uframes_t ;

/* Variables and functions */
 int /*<<< orphan*/  snd_pcm_indirect2_pointer (struct snd_pcm_substream*,struct snd_pcm_indirect2*) ; 
 struct snd_ml403_ac97cr* snd_pcm_substream_chip (struct snd_pcm_substream*) ; 

__attribute__((used)) static snd_pcm_uframes_t
snd_ml403_ac97cr_pcm_pointer(struct snd_pcm_substream *substream)
{
	struct snd_ml403_ac97cr *ml403_ac97cr;
	struct snd_pcm_indirect2 *ind2_rec = NULL;

	ml403_ac97cr = snd_pcm_substream_chip(substream);

	if (substream == ml403_ac97cr->playback_substream)
		ind2_rec = &ml403_ac97cr->ind_rec;
	if (substream == ml403_ac97cr->capture_substream)
		ind2_rec = &ml403_ac97cr->capture_ind2_rec;

	if (ind2_rec != NULL)
		return snd_pcm_indirect2_pointer(substream, ind2_rec);
	return (snd_pcm_uframes_t) 0;
}