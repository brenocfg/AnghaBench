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
typedef  int u32 ;
struct TYPE_5__ {scalar_t__* differed_part_pcm_chunks; } ;
struct TYPE_4__ {scalar_t__* differed_part_pcm_chunks; } ;
struct snd_motu {int /*<<< orphan*/  unit; TYPE_2__ rx_packet_formats; TYPE_1__ tx_packet_formats; } ;
typedef  int /*<<< orphan*/  reg ;
typedef  int /*<<< orphan*/  __be32 ;
struct TYPE_6__ {int max_speed; } ;

/* Variables and functions */
 int /*<<< orphan*/  PACKET_FORMAT_OFFSET ; 
 int RX_PACKET_EXCLUDE_DIFFERED_DATA_CHUNKS ; 
 int TX_PACKET_EXCLUDE_DIFFERED_DATA_CHUNKS ; 
 int TX_PACKET_TRANSMISSION_SPEED_MASK ; 
 int be32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpu_to_be32 (int) ; 
 TYPE_3__* fw_parent_device (int /*<<< orphan*/ ) ; 
 int snd_motu_transaction_read (struct snd_motu*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int snd_motu_transaction_write (struct snd_motu*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int ensure_packet_formats(struct snd_motu *motu)
{
	__be32 reg;
	u32 data;
	int err;

	err = snd_motu_transaction_read(motu, PACKET_FORMAT_OFFSET, &reg,
					sizeof(reg));
	if (err < 0)
		return err;
	data = be32_to_cpu(reg);

	data &= ~(TX_PACKET_EXCLUDE_DIFFERED_DATA_CHUNKS |
		  RX_PACKET_EXCLUDE_DIFFERED_DATA_CHUNKS|
		  TX_PACKET_TRANSMISSION_SPEED_MASK);
	if (motu->tx_packet_formats.differed_part_pcm_chunks[0] == 0)
		data |= TX_PACKET_EXCLUDE_DIFFERED_DATA_CHUNKS;
	if (motu->rx_packet_formats.differed_part_pcm_chunks[0] == 0)
		data |= RX_PACKET_EXCLUDE_DIFFERED_DATA_CHUNKS;
	data |= fw_parent_device(motu->unit)->max_speed;

	reg = cpu_to_be32(data);
	return snd_motu_transaction_write(motu, PACKET_FORMAT_OFFSET, &reg,
					  sizeof(reg));
}