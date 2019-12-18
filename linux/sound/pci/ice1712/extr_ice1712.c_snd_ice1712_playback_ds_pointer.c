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
typedef  int /*<<< orphan*/  u8 ;
struct snd_pcm_substream {int number; TYPE_1__* runtime; } ;
struct snd_ice1712 {int* playback_con_virt_addr; scalar_t__* playback_con_active_buf; } ;
typedef  size_t snd_pcm_uframes_t ;
struct TYPE_2__ {size_t buffer_size; } ;

/* Variables and functions */
 int /*<<< orphan*/  ICE1712_DSC_ADDR0 ; 
 int /*<<< orphan*/  ICE1712_DSC_ADDR1 ; 
 int /*<<< orphan*/  ICE1712_DSC_CONTROL ; 
 size_t bytes_to_frames (TYPE_1__*,size_t) ; 
 int snd_ice1712_ds_read (struct snd_ice1712*,int,int /*<<< orphan*/ ) ; 
 struct snd_ice1712* snd_pcm_substream_chip (struct snd_pcm_substream*) ; 

__attribute__((used)) static snd_pcm_uframes_t snd_ice1712_playback_ds_pointer(struct snd_pcm_substream *substream)
{
	struct snd_ice1712 *ice = snd_pcm_substream_chip(substream);
	u8 addr;
	size_t ptr;

	if (!(snd_ice1712_ds_read(ice, substream->number * 2, ICE1712_DSC_CONTROL) & 1))
		return 0;
	if (ice->playback_con_active_buf[substream->number])
		addr = ICE1712_DSC_ADDR1;
	else
		addr = ICE1712_DSC_ADDR0;
	ptr = snd_ice1712_ds_read(ice, substream->number * 2, addr) -
		ice->playback_con_virt_addr[substream->number];
	ptr = bytes_to_frames(substream->runtime, ptr);
	if (ptr == substream->runtime->buffer_size)
		ptr = 0;
	return ptr;
}