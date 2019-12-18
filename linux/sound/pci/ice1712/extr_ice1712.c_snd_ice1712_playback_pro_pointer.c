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
struct snd_pcm_substream {TYPE_1__* runtime; } ;
struct snd_ice1712 {int playback_pro_size; } ;
typedef  size_t snd_pcm_uframes_t ;
struct TYPE_2__ {size_t buffer_size; } ;

/* Variables and functions */
 int ICE1712_PLAYBACK_START ; 
 int /*<<< orphan*/  ICEMT (struct snd_ice1712*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PLAYBACK_CONTROL ; 
 int /*<<< orphan*/  PLAYBACK_SIZE ; 
 size_t bytes_to_frames (TYPE_1__*,size_t) ; 
 int inl (int /*<<< orphan*/ ) ; 
 int inw (int /*<<< orphan*/ ) ; 
 struct snd_ice1712* snd_pcm_substream_chip (struct snd_pcm_substream*) ; 

__attribute__((used)) static snd_pcm_uframes_t snd_ice1712_playback_pro_pointer(struct snd_pcm_substream *substream)
{
	struct snd_ice1712 *ice = snd_pcm_substream_chip(substream);
	size_t ptr;

	if (!(inl(ICEMT(ice, PLAYBACK_CONTROL)) & ICE1712_PLAYBACK_START))
		return 0;
	ptr = ice->playback_pro_size - (inw(ICEMT(ice, PLAYBACK_SIZE)) << 2);
	ptr = bytes_to_frames(substream->runtime, ptr);
	if (ptr == substream->runtime->buffer_size)
		ptr = 0;
	return ptr;
}