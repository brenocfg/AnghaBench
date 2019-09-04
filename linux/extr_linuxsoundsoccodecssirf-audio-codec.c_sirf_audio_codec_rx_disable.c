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
struct sirf_audio_codec {int /*<<< orphan*/  regmap; } ;

/* Variables and functions */
 int /*<<< orphan*/  AUDIO_PORT_IC_CODEC_RX_CTRL ; 
 int /*<<< orphan*/  IC_RX_ENABLE_STEREO ; 
 int /*<<< orphan*/  regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void sirf_audio_codec_rx_disable(struct sirf_audio_codec *sirf_audio_codec)
{
	regmap_update_bits(sirf_audio_codec->regmap,
			AUDIO_PORT_IC_CODEC_RX_CTRL,
			IC_RX_ENABLE_STEREO, ~IC_RX_ENABLE_STEREO);
}