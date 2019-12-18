#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct TYPE_3__ {unsigned int channel; } ;
struct TYPE_4__ {int /*<<< orphan*/  data_block_quadlets; } ;
struct snd_ff {TYPE_1__ tx_resources; int /*<<< orphan*/  unit; TYPE_2__ tx_stream; } ;
typedef  int /*<<< orphan*/  reg ;
typedef  int /*<<< orphan*/  __le32 ;

/* Variables and functions */
 int ETIMEDOUT ; 
 int /*<<< orphan*/  FF800_ALLOC_TX_STREAM ; 
 int /*<<< orphan*/  FF800_TX_PACKET_ISOC_CH ; 
 int /*<<< orphan*/  TCODE_READ_QUADLET_REQUEST ; 
 int /*<<< orphan*/  TCODE_WRITE_QUADLET_REQUEST ; 
 int /*<<< orphan*/  cpu_to_le32 (int /*<<< orphan*/ ) ; 
 int le32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msleep (int) ; 
 int snd_fw_transaction (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int allocate_tx_resources(struct snd_ff *ff)
{
	__le32 reg;
	unsigned int count;
	unsigned int tx_isoc_channel;
	int err;

	reg = cpu_to_le32(ff->tx_stream.data_block_quadlets);
	err = snd_fw_transaction(ff->unit, TCODE_WRITE_QUADLET_REQUEST,
				 FF800_ALLOC_TX_STREAM, &reg, sizeof(reg), 0);
	if (err < 0)
		return err;

	// Wait till the format of tx packet is available.
	count = 0;
	while (count++ < 10) {
		u32 data;
		err = snd_fw_transaction(ff->unit, TCODE_READ_QUADLET_REQUEST,
				FF800_TX_PACKET_ISOC_CH, &reg, sizeof(reg), 0);
		if (err < 0)
			return err;

		data = le32_to_cpu(reg);
		if (data != 0xffffffff) {
			tx_isoc_channel = data;
			break;
		}

		msleep(50);
	}
	if (count >= 10)
		return -ETIMEDOUT;

	// NOTE: this is a makeshift to start OHCI 1394 IR context in the
	// channel. On the other hand, 'struct fw_iso_resources.allocated' is
	// not true and it's not deallocated at stop.
	ff->tx_resources.channel = tx_isoc_channel;

	return 0;
}