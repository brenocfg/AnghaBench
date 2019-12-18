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

/* Variables and functions */
 int /*<<< orphan*/  AICA_CONTROL_CHANNEL_SAMPLE_NUMBER ; 
 unsigned long readl (int /*<<< orphan*/ ) ; 

__attribute__((used)) static unsigned long snd_aicapcm_pcm_pointer(struct snd_pcm_substream
					     *substream)
{
	return readl(AICA_CONTROL_CHANNEL_SAMPLE_NUMBER);
}