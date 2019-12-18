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
struct atiixp {int /*<<< orphan*/ * dmas; } ;

/* Variables and functions */
 size_t ATI_DMA_CAPTURE ; 
 int snd_atiixp_pcm_open (struct snd_pcm_substream*,int /*<<< orphan*/ *,int) ; 
 struct atiixp* snd_pcm_substream_chip (struct snd_pcm_substream*) ; 

__attribute__((used)) static int snd_atiixp_capture_open(struct snd_pcm_substream *substream)
{
	struct atiixp *chip = snd_pcm_substream_chip(substream);
	return snd_atiixp_pcm_open(substream, &chip->dmas[ATI_DMA_CAPTURE], 1);
}