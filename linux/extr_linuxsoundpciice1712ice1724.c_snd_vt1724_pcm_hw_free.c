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
struct snd_ice1712 {int /*<<< orphan*/  open_mutex; struct snd_pcm_substream** pcm_reserved; } ;

/* Variables and functions */
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int snd_pcm_lib_free_pages (struct snd_pcm_substream*) ; 
 struct snd_ice1712* snd_pcm_substream_chip (struct snd_pcm_substream*) ; 

__attribute__((used)) static int snd_vt1724_pcm_hw_free(struct snd_pcm_substream *substream)
{
	struct snd_ice1712 *ice = snd_pcm_substream_chip(substream);
	int i;

	mutex_lock(&ice->open_mutex);
	/* unmark surround channels */
	for (i = 0; i < 3; i++)
		if (ice->pcm_reserved[i] == substream)
			ice->pcm_reserved[i] = NULL;
	mutex_unlock(&ice->open_mutex);
	return snd_pcm_lib_free_pages(substream);
}