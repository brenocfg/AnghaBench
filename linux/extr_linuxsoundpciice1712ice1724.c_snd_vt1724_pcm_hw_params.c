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
struct snd_ice1712 {int /*<<< orphan*/  open_mutex; struct snd_pcm_substream** pcm_reserved; struct snd_pcm_substream** playback_con_substream_ds; struct snd_pcm_substream* playback_pro_substream; } ;

/* Variables and functions */
 int EBUSY ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  params_buffer_bytes (struct snd_pcm_hw_params*) ; 
 int params_channels (struct snd_pcm_hw_params*) ; 
 int /*<<< orphan*/  params_rate (struct snd_pcm_hw_params*) ; 
 int snd_pcm_lib_malloc_pages (struct snd_pcm_substream*,int /*<<< orphan*/ ) ; 
 struct snd_ice1712* snd_pcm_substream_chip (struct snd_pcm_substream*) ; 
 int snd_vt1724_set_pro_rate (struct snd_ice1712*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int snd_vt1724_pcm_hw_params(struct snd_pcm_substream *substream,
				    struct snd_pcm_hw_params *hw_params)
{
	struct snd_ice1712 *ice = snd_pcm_substream_chip(substream);
	int i, chs, err;

	chs = params_channels(hw_params);
	mutex_lock(&ice->open_mutex);
	/* mark surround channels */
	if (substream == ice->playback_pro_substream) {
		/* PDMA0 can be multi-channel up to 8 */
		chs = chs / 2 - 1;
		for (i = 0; i < chs; i++) {
			if (ice->pcm_reserved[i] &&
			    ice->pcm_reserved[i] != substream) {
				mutex_unlock(&ice->open_mutex);
				return -EBUSY;
			}
			ice->pcm_reserved[i] = substream;
		}
		for (; i < 3; i++) {
			if (ice->pcm_reserved[i] == substream)
				ice->pcm_reserved[i] = NULL;
		}
	} else {
		for (i = 0; i < 3; i++) {
			/* check individual playback stream */
			if (ice->playback_con_substream_ds[i] == substream) {
				if (ice->pcm_reserved[i] &&
				    ice->pcm_reserved[i] != substream) {
					mutex_unlock(&ice->open_mutex);
					return -EBUSY;
				}
				ice->pcm_reserved[i] = substream;
				break;
			}
		}
	}
	mutex_unlock(&ice->open_mutex);

	err = snd_vt1724_set_pro_rate(ice, params_rate(hw_params), 0);
	if (err < 0)
		return err;

	return snd_pcm_lib_malloc_pages(substream, params_buffer_bytes(hw_params));
}