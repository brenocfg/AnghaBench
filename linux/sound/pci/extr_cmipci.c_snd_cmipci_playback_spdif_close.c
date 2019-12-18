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
struct cmipci {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CM_OPEN_SPDIF_PLAYBACK ; 
 int /*<<< orphan*/  close_device_check (struct cmipci*,int /*<<< orphan*/ ) ; 
 struct cmipci* snd_pcm_substream_chip (struct snd_pcm_substream*) ; 

__attribute__((used)) static int snd_cmipci_playback_spdif_close(struct snd_pcm_substream *substream)
{
	struct cmipci *cm = snd_pcm_substream_chip(substream);
	close_device_check(cm, CM_OPEN_SPDIF_PLAYBACK);
	return 0;
}