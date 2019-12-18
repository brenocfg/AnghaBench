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
typedef  int uint32_t ;
struct ssp_device {int dummy; } ;
struct snd_pcm_substream {scalar_t__ stream; } ;

/* Variables and functions */
 scalar_t__ SNDRV_PCM_STREAM_PLAYBACK ; 
 int /*<<< orphan*/  SSCR0 ; 
 int SSCR0_SSE ; 
 int /*<<< orphan*/  SSCR1 ; 
 int SSCR1_RSRE ; 
 int SSCR1_TSRE ; 
 int /*<<< orphan*/  SSPSP ; 
 int /*<<< orphan*/  SSSR ; 
 int pxa_ssp_read_reg (struct ssp_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pxa_ssp_write_reg (struct ssp_device*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void pxa_ssp_set_running_bit(struct snd_pcm_substream *substream,
				    struct ssp_device *ssp, int value)
{
	uint32_t sscr0 = pxa_ssp_read_reg(ssp, SSCR0);
	uint32_t sscr1 = pxa_ssp_read_reg(ssp, SSCR1);
	uint32_t sspsp = pxa_ssp_read_reg(ssp, SSPSP);
	uint32_t sssr = pxa_ssp_read_reg(ssp, SSSR);

	if (value && (sscr0 & SSCR0_SSE))
		pxa_ssp_write_reg(ssp, SSCR0, sscr0 & ~SSCR0_SSE);

	if (substream->stream == SNDRV_PCM_STREAM_PLAYBACK) {
		if (value)
			sscr1 |= SSCR1_TSRE;
		else
			sscr1 &= ~SSCR1_TSRE;
	} else {
		if (value)
			sscr1 |= SSCR1_RSRE;
		else
			sscr1 &= ~SSCR1_RSRE;
	}

	pxa_ssp_write_reg(ssp, SSCR1, sscr1);

	if (value) {
		pxa_ssp_write_reg(ssp, SSSR, sssr);
		pxa_ssp_write_reg(ssp, SSPSP, sspsp);
		pxa_ssp_write_reg(ssp, SSCR0, sscr0 | SSCR0_SSE);
	}
}