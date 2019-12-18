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
 int /*<<< orphan*/  AUDIO_FIFO_RESET ; 
 int /*<<< orphan*/  AUDIO_FIFO_START ; 
 int /*<<< orphan*/  AUDIO_PORT_IC_CODEC_TX_CTRL ; 
 int /*<<< orphan*/  AUDIO_PORT_IC_TXFIFO_INT_MSK ; 
 int /*<<< orphan*/  AUDIO_PORT_IC_TXFIFO_OP ; 
 int /*<<< orphan*/  IC_TX_ENABLE ; 
 int /*<<< orphan*/  regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  regmap_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void sirf_audio_codec_tx_enable(struct sirf_audio_codec *sirf_audio_codec)
{
	regmap_update_bits(sirf_audio_codec->regmap, AUDIO_PORT_IC_TXFIFO_OP,
		AUDIO_FIFO_RESET, AUDIO_FIFO_RESET);
	regmap_update_bits(sirf_audio_codec->regmap, AUDIO_PORT_IC_TXFIFO_OP,
		AUDIO_FIFO_RESET, ~AUDIO_FIFO_RESET);
	regmap_write(sirf_audio_codec->regmap, AUDIO_PORT_IC_TXFIFO_INT_MSK, 0);
	regmap_write(sirf_audio_codec->regmap, AUDIO_PORT_IC_TXFIFO_OP, 0);
	regmap_update_bits(sirf_audio_codec->regmap, AUDIO_PORT_IC_TXFIFO_OP,
		AUDIO_FIFO_START, AUDIO_FIFO_START);
	regmap_update_bits(sirf_audio_codec->regmap,
		AUDIO_PORT_IC_CODEC_TX_CTRL, IC_TX_ENABLE, IC_TX_ENABLE);
}