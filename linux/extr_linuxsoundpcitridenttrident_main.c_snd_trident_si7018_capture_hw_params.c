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
 int /*<<< orphan*/  params_buffer_bytes (struct snd_pcm_hw_params*) ; 
 int snd_pcm_lib_malloc_pages (struct snd_pcm_substream*,int /*<<< orphan*/ ) ; 
 int snd_trident_allocate_evoice (struct snd_pcm_substream*,struct snd_pcm_hw_params*) ; 

__attribute__((used)) static int snd_trident_si7018_capture_hw_params(struct snd_pcm_substream *substream,
						struct snd_pcm_hw_params *hw_params)
{
	int err;

	if ((err = snd_pcm_lib_malloc_pages(substream, params_buffer_bytes(hw_params))) < 0)
		return err;

	return snd_trident_allocate_evoice(substream, hw_params);
}