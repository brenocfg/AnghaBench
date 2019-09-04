#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int data_block_quadlets; } ;
struct TYPE_7__ {int channel; } ;
struct TYPE_6__ {int channel; } ;
struct TYPE_5__ {int data_block_quadlets; } ;
struct snd_ff {int /*<<< orphan*/  unit; TYPE_4__ tx_stream; TYPE_3__ tx_resources; TYPE_2__ rx_resources; TYPE_1__ rx_stream; } ;
typedef  int /*<<< orphan*/  reg ;
typedef  int /*<<< orphan*/  __le32 ;

/* Variables and functions */
 int CIP_SFC_COUNT ; 
 int EINVAL ; 
 int /*<<< orphan*/  FF400_ISOC_COMM_START ; 
 int /*<<< orphan*/  FF400_RX_PACKET_FORMAT ; 
 int /*<<< orphan*/  FF400_STF ; 
 int /*<<< orphan*/  FF400_TX_PACKET_FORMAT ; 
 int /*<<< orphan*/  TCODE_WRITE_QUADLET_REQUEST ; 
 unsigned int* amdtp_rate_table ; 
 int /*<<< orphan*/  cpu_to_le32 (int) ; 
 int /*<<< orphan*/  msleep (int) ; 
 int snd_fw_transaction (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ff400_begin_session(struct snd_ff *ff, unsigned int rate)
{
	__le32 reg;
	int i, err;

	/* Check whether the given value is supported or not. */
	for (i = 0; i < CIP_SFC_COUNT; i++) {
		if (amdtp_rate_table[i] == rate)
			break;
	}
	if (i == CIP_SFC_COUNT)
		return -EINVAL;

	/* Set the number of data blocks transferred in a second. */
	reg = cpu_to_le32(rate);
	err = snd_fw_transaction(ff->unit, TCODE_WRITE_QUADLET_REQUEST,
				 FF400_STF, &reg, sizeof(reg), 0);
	if (err < 0)
		return err;

	msleep(100);

	/*
	 * Set isochronous channel and the number of quadlets of received
	 * packets.
	 */
	reg = cpu_to_le32(((ff->rx_stream.data_block_quadlets << 3) << 8) |
			  ff->rx_resources.channel);
	err = snd_fw_transaction(ff->unit, TCODE_WRITE_QUADLET_REQUEST,
				 FF400_RX_PACKET_FORMAT, &reg, sizeof(reg), 0);
	if (err < 0)
		return err;

	/*
	 * Set isochronous channel and the number of quadlets of transmitted
	 * packet.
	 */
	/* TODO: investigate the purpose of this 0x80. */
	reg = cpu_to_le32((0x80 << 24) |
			  (ff->tx_resources.channel << 5) |
			  (ff->tx_stream.data_block_quadlets));
	err = snd_fw_transaction(ff->unit, TCODE_WRITE_QUADLET_REQUEST,
				 FF400_TX_PACKET_FORMAT, &reg, sizeof(reg), 0);
	if (err < 0)
		return err;

	/* Allow to transmit packets. */
	reg = cpu_to_le32(0x00000001);
	return snd_fw_transaction(ff->unit, TCODE_WRITE_QUADLET_REQUEST,
				 FF400_ISOC_COMM_START, &reg, sizeof(reg), 0);
}