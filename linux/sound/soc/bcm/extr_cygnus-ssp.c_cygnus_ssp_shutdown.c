#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  size_t u32 ;
struct snd_soc_dai {int dummy; } ;
struct snd_pcm_substream {scalar_t__ stream; } ;
struct TYPE_6__ {int play_en; int cap_en; int play_clk_en; int cap_clk_en; } ;
struct TYPE_4__ {scalar_t__ i2s_mclk_cfg; } ;
struct cygnus_aio_port {TYPE_3__ clk_trace; TYPE_2__* cygaud; TYPE_1__ regs; int /*<<< orphan*/  is_slave; } ;
struct TYPE_5__ {int /*<<< orphan*/ * audio_clk; int /*<<< orphan*/  dev; scalar_t__ audio; } ;

/* Variables and functions */
 size_t ARRAY_SIZE (int /*<<< orphan*/ *) ; 
 size_t CYGNUS_PLLCLKSEL_MASK ; 
 scalar_t__ SNDRV_PCM_STREAM_PLAYBACK ; 
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 
 struct cygnus_aio_port* cygnus_dai_get_portinfo (struct snd_soc_dai*) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,size_t) ; 
 size_t readl (scalar_t__) ; 

__attribute__((used)) static void cygnus_ssp_shutdown(struct snd_pcm_substream *substream,
			       struct snd_soc_dai *dai)
{
	struct cygnus_aio_port *aio = cygnus_dai_get_portinfo(dai);

	if (substream->stream == SNDRV_PCM_STREAM_PLAYBACK)
		aio->clk_trace.play_en = false;
	else
		aio->clk_trace.cap_en = false;

	if (!aio->is_slave) {
		u32 val;

		val = readl(aio->cygaud->audio + aio->regs.i2s_mclk_cfg);
		val &= CYGNUS_PLLCLKSEL_MASK;
		if (val >= ARRAY_SIZE(aio->cygaud->audio_clk)) {
			dev_err(aio->cygaud->dev, "Clk index %u is out of bounds\n",
				val);
			return;
		}

		if (substream->stream == SNDRV_PCM_STREAM_PLAYBACK) {
			if (aio->clk_trace.play_clk_en) {
				clk_disable_unprepare(aio->cygaud->
						audio_clk[val]);
				aio->clk_trace.play_clk_en = false;
			}
		} else {
			if (aio->clk_trace.cap_clk_en) {
				clk_disable_unprepare(aio->cygaud->
						audio_clk[val]);
				aio->clk_trace.cap_clk_en = false;
			}
		}
	}
}