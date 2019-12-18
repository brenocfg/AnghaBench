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
struct snd_pcm_hw_params {int dummy; } ;

/* Variables and functions */
 int snd_trident_allocate_evoice (struct snd_pcm_substream*,struct snd_pcm_hw_params*) ; 
 int snd_trident_allocate_pcm_mem (struct snd_pcm_substream*,struct snd_pcm_hw_params*) ; 

__attribute__((used)) static int snd_trident_hw_params(struct snd_pcm_substream *substream,
				 struct snd_pcm_hw_params *hw_params)
{
	int err;

	err = snd_trident_allocate_pcm_mem(substream, hw_params);
	if (err >= 0)
		err = snd_trident_allocate_evoice(substream, hw_params);
	return err;
}