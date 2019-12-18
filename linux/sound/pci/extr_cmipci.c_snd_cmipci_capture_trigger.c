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
struct cmipci {int /*<<< orphan*/ * channel; } ;

/* Variables and functions */
 size_t CM_CH_CAPT ; 
 int snd_cmipci_pcm_trigger (struct cmipci*,int /*<<< orphan*/ *,int) ; 
 struct cmipci* snd_pcm_substream_chip (struct snd_pcm_substream*) ; 

__attribute__((used)) static int snd_cmipci_capture_trigger(struct snd_pcm_substream *substream,
				     int cmd)
{
	struct cmipci *cm = snd_pcm_substream_chip(substream);
	return snd_cmipci_pcm_trigger(cm, &cm->channel[CM_CH_CAPT], cmd);
}