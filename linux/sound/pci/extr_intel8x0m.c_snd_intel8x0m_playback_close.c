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
struct intel8x0m {TYPE_1__* ichd; } ;
struct TYPE_2__ {int /*<<< orphan*/ * substream; } ;

/* Variables and functions */
 size_t ICHD_MDMOUT ; 
 struct intel8x0m* snd_pcm_substream_chip (struct snd_pcm_substream*) ; 

__attribute__((used)) static int snd_intel8x0m_playback_close(struct snd_pcm_substream *substream)
{
	struct intel8x0m *chip = snd_pcm_substream_chip(substream);

	chip->ichd[ICHD_MDMOUT].substream = NULL;
	return 0;
}