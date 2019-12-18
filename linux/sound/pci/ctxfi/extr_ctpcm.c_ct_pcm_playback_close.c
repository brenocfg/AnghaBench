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
struct snd_pcm_substream {TYPE_1__* pcm; } ;
struct ct_atc {int /*<<< orphan*/  (* spdif_out_passthru ) (struct ct_atc*,int /*<<< orphan*/ ) ;} ;
struct TYPE_2__ {scalar_t__ device; } ;

/* Variables and functions */
 scalar_t__ IEC958 ; 
 struct ct_atc* snd_pcm_substream_chip (struct snd_pcm_substream*) ; 
 int /*<<< orphan*/  stub1 (struct ct_atc*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ct_pcm_playback_close(struct snd_pcm_substream *substream)
{
	struct ct_atc *atc = snd_pcm_substream_chip(substream);

	/* TODO: Notify mixer inactive. */
	if (IEC958 == substream->pcm->device)
		atc->spdif_out_passthru(atc, 0);

	/* The ct_atc_pcm object will be freed by runtime->private_free */

	return 0;
}