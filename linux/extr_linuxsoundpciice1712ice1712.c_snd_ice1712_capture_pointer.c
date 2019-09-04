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
struct snd_ice1712 {size_t capture_con_virt_addr; } ;
typedef  size_t snd_pcm_uframes_t ;
struct TYPE_2__ {size_t buffer_size; } ;

/* Variables and functions */
 int /*<<< orphan*/  CONCAP_ADDR ; 
 int /*<<< orphan*/  ICE1712_IREG_CAP_CTRL ; 
 int /*<<< orphan*/  ICEREG (struct snd_ice1712*,int /*<<< orphan*/ ) ; 
 size_t bytes_to_frames (TYPE_1__*,size_t) ; 
 size_t inl (int /*<<< orphan*/ ) ; 
 int snd_ice1712_read (struct snd_ice1712*,int /*<<< orphan*/ ) ; 
 struct snd_ice1712* snd_pcm_substream_chip (struct snd_pcm_substream*) ; 

__attribute__((used)) static snd_pcm_uframes_t snd_ice1712_capture_pointer(struct snd_pcm_substream *substream)
{
	struct snd_ice1712 *ice = snd_pcm_substream_chip(substream);
	size_t ptr;

	if (!(snd_ice1712_read(ice, ICE1712_IREG_CAP_CTRL) & 1))
		return 0;
	ptr = inl(ICEREG(ice, CONCAP_ADDR)) - ice->capture_con_virt_addr;
	ptr = bytes_to_frames(substream->runtime, ptr);
	if (ptr == substream->runtime->buffer_size)
		ptr = 0;
	return ptr;
}