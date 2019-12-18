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
struct snd_pcm_substream {size_t stream; } ;
struct hda_pcm_stream {int dummy; } ;
struct azx_pcm {TYPE_1__* info; } ;
struct TYPE_2__ {struct hda_pcm_stream* stream; } ;

/* Variables and functions */
 struct azx_pcm* snd_pcm_substream_chip (struct snd_pcm_substream*) ; 

__attribute__((used)) static inline struct hda_pcm_stream *
to_hda_pcm_stream(struct snd_pcm_substream *substream)
{
	struct azx_pcm *apcm = snd_pcm_substream_chip(substream);
	return &apcm->info->stream[substream->stream];
}