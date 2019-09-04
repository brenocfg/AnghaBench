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
typedef  int /*<<< orphan*/  u64 ;
typedef  unsigned int u32 ;
struct snd_dice {unsigned int clock_caps; int /*<<< orphan*/  rx_midi_ports; int /*<<< orphan*/  rx_pcm_chs; int /*<<< orphan*/  tx_midi_ports; int /*<<< orphan*/  tx_pcm_chs; } ;
typedef  int /*<<< orphan*/  reg ;
typedef  int /*<<< orphan*/  __be32 ;

/* Variables and functions */
 unsigned int CLOCK_CAP_RATE_176400 ; 
 unsigned int CLOCK_CAP_RATE_192000 ; 
 unsigned int CLOCK_CAP_RATE_32000 ; 
 unsigned int CLOCK_CAP_RATE_44100 ; 
 unsigned int CLOCK_CAP_RATE_48000 ; 
 unsigned int CLOCK_CAP_RATE_88200 ; 
 unsigned int CLOCK_CAP_RATE_96000 ; 
 scalar_t__ EXT_APP_STREAM_ENTRIES ; 
 unsigned int EXT_APP_STREAM_ENTRY_SIZE ; 
 scalar_t__ EXT_APP_STREAM_TX_NUMBER ; 
 int SND_DICE_RATE_MODE_COUNT ; 
 unsigned int be32_to_cpu (int /*<<< orphan*/ ) ; 
 int read_stream_entries (struct snd_dice*,int /*<<< orphan*/ ,unsigned int,unsigned int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int read_transaction (struct snd_dice*,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ **,int) ; 

__attribute__((used)) static int detect_stream_formats(struct snd_dice *dice, u64 section_addr)
{
	u32 base_offset;
	__be32 reg[2];
	unsigned int stream_count;
	int mode;
	int err = 0;

	for (mode = 0; mode < SND_DICE_RATE_MODE_COUNT; ++mode) {
		unsigned int cap;

		/*
		 * Some models report stream formats at highest mode, however
		 * they don't support the mode. Check clock capabilities.
		 */
		if (mode == 2) {
			cap = CLOCK_CAP_RATE_176400 | CLOCK_CAP_RATE_192000;
		} else if (mode == 1) {
			cap = CLOCK_CAP_RATE_88200 | CLOCK_CAP_RATE_96000;
		} else {
			cap = CLOCK_CAP_RATE_32000 | CLOCK_CAP_RATE_44100 |
			      CLOCK_CAP_RATE_48000;
		}
		if (!(cap & dice->clock_caps))
			continue;

		base_offset = 0x2000 * mode + 0x1000;

		err = read_transaction(dice, section_addr,
				       base_offset + EXT_APP_STREAM_TX_NUMBER,
				       &reg, sizeof(reg));
		if (err < 0)
			break;

		base_offset += EXT_APP_STREAM_ENTRIES;
		stream_count = be32_to_cpu(reg[0]);
		err = read_stream_entries(dice, section_addr, base_offset,
					  stream_count, mode,
					  dice->tx_pcm_chs,
					  dice->tx_midi_ports);
		if (err < 0)
			break;

		base_offset += stream_count * EXT_APP_STREAM_ENTRY_SIZE;
		stream_count = be32_to_cpu(reg[1]);
		err = read_stream_entries(dice, section_addr, base_offset,
					  stream_count,
					  mode, dice->rx_pcm_chs,
					  dice->rx_midi_ports);
		if (err < 0)
			break;
	}

	return err;
}