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
struct snd_pcm_substream {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  pcm_rec; } ;
struct snd_cs46xx {TYPE_1__ capt; } ;

/* Variables and functions */
 int /*<<< orphan*/  snd_cs46xx_cp_trans_copy ; 
 int snd_pcm_indirect_capture_transfer (struct snd_pcm_substream*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct snd_cs46xx* snd_pcm_substream_chip (struct snd_pcm_substream*) ; 

__attribute__((used)) static int snd_cs46xx_capture_transfer(struct snd_pcm_substream *substream)
{
	struct snd_cs46xx *chip = snd_pcm_substream_chip(substream);
	return snd_pcm_indirect_capture_transfer(substream, &chip->capt.pcm_rec,
						 snd_cs46xx_cp_trans_copy);
}