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
struct snd_dice {unsigned int** tx_pcm_chs; unsigned int* tx_midi_ports; unsigned int** rx_pcm_chs; unsigned int* rx_midi_ports; TYPE_1__* unit; struct fw_iso_resources* rx_resources; struct amdtp_stream* rx_stream; struct fw_iso_resources* tx_resources; struct amdtp_stream* tx_stream; } ;
struct reg_params {unsigned int count; unsigned int size; } ;
struct fw_iso_resources {int /*<<< orphan*/  channel; } ;
struct fw_device {int /*<<< orphan*/  max_speed; } ;
struct amdtp_stream {int dummy; } ;
typedef  int /*<<< orphan*/  reg ;
typedef  enum snd_dice_rate_mode { ____Placeholder_snd_dice_rate_mode } snd_dice_rate_mode ;
typedef  enum amdtp_stream_direction { ____Placeholder_amdtp_stream_direction } amdtp_stream_direction ;
typedef  int /*<<< orphan*/  __be32 ;
struct TYPE_2__ {int /*<<< orphan*/  device; } ;

/* Variables and functions */
 int AMDTP_IN_STREAM ; 
 int EPROTO ; 
 scalar_t__ RX_ISOCHRONOUS ; 
 scalar_t__ RX_NUMBER_AUDIO ; 
 scalar_t__ TX_ISOCHRONOUS ; 
 scalar_t__ TX_NUMBER_AUDIO ; 
 scalar_t__ TX_SPEED ; 
 int amdtp_stream_start (struct amdtp_stream*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 unsigned int be32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpu_to_be32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*,unsigned int,unsigned int,unsigned int,unsigned int) ; 
 struct fw_device* fw_parent_device (TYPE_1__*) ; 
 int keep_resources (struct snd_dice*,int,unsigned int,unsigned int,unsigned int,unsigned int) ; 
 int snd_dice_stream_get_rate_mode (struct snd_dice*,unsigned int,int*) ; 
 int snd_dice_transaction_read_rx (struct snd_dice*,scalar_t__,int /*<<< orphan*/ *,int) ; 
 int snd_dice_transaction_read_tx (struct snd_dice*,scalar_t__,int /*<<< orphan*/ *,int) ; 
 int snd_dice_transaction_write_rx (struct snd_dice*,scalar_t__,int /*<<< orphan*/ *,int) ; 
 int snd_dice_transaction_write_tx (struct snd_dice*,scalar_t__,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int start_streams(struct snd_dice *dice, enum amdtp_stream_direction dir,
			 unsigned int rate, struct reg_params *params)
{
	__be32 reg[2];
	enum snd_dice_rate_mode mode;
	unsigned int i, pcm_chs, midi_ports;
	struct amdtp_stream *streams;
	struct fw_iso_resources *resources;
	struct fw_device *fw_dev = fw_parent_device(dice->unit);
	int err = 0;

	if (dir == AMDTP_IN_STREAM) {
		streams = dice->tx_stream;
		resources = dice->tx_resources;
	} else {
		streams = dice->rx_stream;
		resources = dice->rx_resources;
	}

	err = snd_dice_stream_get_rate_mode(dice, rate, &mode);
	if (err < 0)
		return err;

	for (i = 0; i < params->count; i++) {
		unsigned int pcm_cache;
		unsigned int midi_cache;

		if (dir == AMDTP_IN_STREAM) {
			pcm_cache = dice->tx_pcm_chs[i][mode];
			midi_cache = dice->tx_midi_ports[i];
			err = snd_dice_transaction_read_tx(dice,
					params->size * i + TX_NUMBER_AUDIO,
					reg, sizeof(reg));
		} else {
			pcm_cache = dice->rx_pcm_chs[i][mode];
			midi_cache = dice->rx_midi_ports[i];
			err = snd_dice_transaction_read_rx(dice,
					params->size * i + RX_NUMBER_AUDIO,
					reg, sizeof(reg));
		}
		if (err < 0)
			return err;
		pcm_chs = be32_to_cpu(reg[0]);
		midi_ports = be32_to_cpu(reg[1]);

		/* These are important for developer of this driver. */
		if (pcm_chs != pcm_cache || midi_ports != midi_cache) {
			dev_info(&dice->unit->device,
				 "cache mismatch: pcm: %u:%u, midi: %u:%u\n",
				 pcm_chs, pcm_cache, midi_ports, midi_cache);
			return -EPROTO;
		}

		err = keep_resources(dice, dir, i, rate, pcm_chs, midi_ports);
		if (err < 0)
			return err;

		reg[0] = cpu_to_be32(resources[i].channel);
		if (dir == AMDTP_IN_STREAM) {
			err = snd_dice_transaction_write_tx(dice,
					params->size * i + TX_ISOCHRONOUS,
					reg, sizeof(reg[0]));
		} else {
			err = snd_dice_transaction_write_rx(dice,
					params->size * i + RX_ISOCHRONOUS,
					reg, sizeof(reg[0]));
		}
		if (err < 0)
			return err;

		if (dir == AMDTP_IN_STREAM) {
			reg[0] = cpu_to_be32(fw_dev->max_speed);
			err = snd_dice_transaction_write_tx(dice,
					params->size * i + TX_SPEED,
					reg, sizeof(reg[0]));
			if (err < 0)
				return err;
		}

		err = amdtp_stream_start(&streams[i], resources[i].channel,
					 fw_dev->max_speed);
		if (err < 0)
			return err;
	}

	return err;
}