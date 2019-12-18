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
struct TYPE_5__ {int channel; } ;
struct TYPE_6__ {int data_block_quadlets; } ;
struct snd_ff {int /*<<< orphan*/  unit; TYPE_2__ rx_resources; TYPE_3__ rx_stream; } ;
typedef  int /*<<< orphan*/  reg ;
typedef  int /*<<< orphan*/  __le32 ;
struct TYPE_4__ {int /*<<< orphan*/  max_speed; } ;

/* Variables and functions */
 int /*<<< orphan*/  FF800_RX_PACKET_FORMAT ; 
 int /*<<< orphan*/  FF800_STF ; 
 int /*<<< orphan*/  TCODE_WRITE_QUADLET_REQUEST ; 
 int allocate_tx_resources (struct snd_ff*) ; 
 int /*<<< orphan*/  amdtp_stream_get_max_payload (TYPE_3__*) ; 
 int /*<<< orphan*/  cpu_to_le32 (int) ; 
 int fw_iso_resources_allocate (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_1__* fw_parent_device (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msleep (int) ; 
 int snd_fw_transaction (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ff800_allocate_resources(struct snd_ff *ff, unsigned int rate)
{
	u32 data;
	__le32 reg;
	int err;

	reg = cpu_to_le32(rate);
	err = snd_fw_transaction(ff->unit, TCODE_WRITE_QUADLET_REQUEST,
				 FF800_STF, &reg, sizeof(reg), 0);
	if (err < 0)
		return err;

	// If starting isochronous communication immediately, change of STF has
	// no effect. In this case, the communication runs based on former STF.
	// Let's sleep for a bit.
	msleep(100);

	// Controllers should allocate isochronous resources for rx stream.
	err = fw_iso_resources_allocate(&ff->rx_resources,
				amdtp_stream_get_max_payload(&ff->rx_stream),
				fw_parent_device(ff->unit)->max_speed);
	if (err < 0)
		return err;

	// Set isochronous channel and the number of quadlets of rx packets.
	// This should be done before the allocation of tx resources to avoid
	// periodical noise.
	data = ff->rx_stream.data_block_quadlets << 3;
	data = (data << 8) | ff->rx_resources.channel;
	reg = cpu_to_le32(data);
	err = snd_fw_transaction(ff->unit, TCODE_WRITE_QUADLET_REQUEST,
				 FF800_RX_PACKET_FORMAT, &reg, sizeof(reg), 0);
	if (err < 0)
		return err;

	return allocate_tx_resources(ff);
}