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
struct usX2Ydev {int rate; } ;
struct snd_pcm_runtime {int buffer_size; } ;

/* Variables and functions */

__attribute__((used)) static inline int usX2Y_iso_frames_per_buffer(struct snd_pcm_runtime *runtime,
					      struct usX2Ydev * usX2Y)
{
	return (runtime->buffer_size * 1000) / usX2Y->rate + 1;	//FIXME: so far only correct period_size == 2^x ?
}