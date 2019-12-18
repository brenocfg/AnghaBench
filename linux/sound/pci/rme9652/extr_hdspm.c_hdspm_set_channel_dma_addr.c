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
struct hdspm {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  hdspm_write (struct hdspm*,unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_pcm_sgbuf_get_addr (struct snd_pcm_substream*,int) ; 

__attribute__((used)) static void hdspm_set_channel_dma_addr(struct hdspm *hdspm,
				       struct snd_pcm_substream *substream,
				       unsigned int reg, int channel)
{
	int i;

	for (i = channel * 16; i < channel * 16 + 16; i++)
		hdspm_write(hdspm, reg + 4 * i,
			    snd_pcm_sgbuf_get_addr(substream, 4096 * i));
}