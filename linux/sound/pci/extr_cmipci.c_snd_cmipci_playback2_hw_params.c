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
struct cmipci {int /*<<< orphan*/  open_mutex; scalar_t__* opened; } ;

/* Variables and functions */
 size_t CM_CH_PLAY ; 
 scalar_t__ CM_OPEN_PLAYBACK_MULTI ; 
 int EBUSY ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  params_buffer_bytes (struct snd_pcm_hw_params*) ; 
 int params_channels (struct snd_pcm_hw_params*) ; 
 int snd_pcm_lib_malloc_pages (struct snd_pcm_substream*,int /*<<< orphan*/ ) ; 
 struct cmipci* snd_pcm_substream_chip (struct snd_pcm_substream*) ; 

__attribute__((used)) static int snd_cmipci_playback2_hw_params(struct snd_pcm_substream *substream,
					  struct snd_pcm_hw_params *hw_params)
{
	struct cmipci *cm = snd_pcm_substream_chip(substream);
	if (params_channels(hw_params) > 2) {
		mutex_lock(&cm->open_mutex);
		if (cm->opened[CM_CH_PLAY]) {
			mutex_unlock(&cm->open_mutex);
			return -EBUSY;
		}
		/* reserve the channel A */
		cm->opened[CM_CH_PLAY] = CM_OPEN_PLAYBACK_MULTI;
		mutex_unlock(&cm->open_mutex);
	}
	return snd_pcm_lib_malloc_pages(substream, params_buffer_bytes(hw_params));
}