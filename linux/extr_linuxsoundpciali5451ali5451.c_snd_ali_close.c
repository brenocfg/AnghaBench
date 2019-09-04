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
struct snd_ali_voice {int /*<<< orphan*/  number; } ;
struct snd_ali {int dummy; } ;
struct TYPE_2__ {struct snd_ali_voice* private_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  snd_ali_disable_special_channel (struct snd_ali*,int /*<<< orphan*/ ) ; 
 struct snd_ali* snd_pcm_substream_chip (struct snd_pcm_substream*) ; 

__attribute__((used)) static int snd_ali_close(struct snd_pcm_substream *substream)
{
	struct snd_ali *codec = snd_pcm_substream_chip(substream);
	struct snd_ali_voice *pvoice = substream->runtime->private_data;

	snd_ali_disable_special_channel(codec,pvoice->number);

	return 0;
}