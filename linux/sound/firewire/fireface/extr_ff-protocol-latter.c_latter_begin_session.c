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
typedef  unsigned int u32 ;
struct TYPE_6__ {unsigned int generation; int channel; } ;
struct snd_ff {int /*<<< orphan*/  unit; TYPE_3__ rx_resources; TYPE_3__ tx_resources; } ;
typedef  int /*<<< orphan*/  reg ;
typedef  int /*<<< orphan*/  __le32 ;
struct TYPE_5__ {TYPE_1__* card; } ;
struct TYPE_4__ {unsigned int generation; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  LATTER_ISOC_CHANNELS ; 
 int /*<<< orphan*/  LATTER_ISOC_START ; 
 int /*<<< orphan*/  TCODE_WRITE_QUADLET_REQUEST ; 
 int /*<<< orphan*/  cpu_to_le32 (unsigned int) ; 
 int fw_iso_resources_update (TYPE_3__*) ; 
 TYPE_2__* fw_parent_device (int /*<<< orphan*/ ) ; 
 int snd_fw_transaction (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int latter_begin_session(struct snd_ff *ff, unsigned int rate)
{
	unsigned int generation = ff->rx_resources.generation;
	unsigned int flag;
	u32 data;
	__le32 reg;
	int err;

	if (rate >= 32000 && rate <= 48000)
		flag = 0x92;
	else if (rate >= 64000 && rate <= 96000)
		flag = 0x8e;
	else if (rate >= 128000 && rate <= 192000)
		flag = 0x8c;
	else
		return -EINVAL;

	if (generation != fw_parent_device(ff->unit)->card->generation) {
		err = fw_iso_resources_update(&ff->tx_resources);
		if (err < 0)
			return err;

		err = fw_iso_resources_update(&ff->rx_resources);
		if (err < 0)
			return err;
	}

	data = (ff->tx_resources.channel << 8) | ff->rx_resources.channel;
	reg = cpu_to_le32(data);
	err = snd_fw_transaction(ff->unit, TCODE_WRITE_QUADLET_REQUEST,
				 LATTER_ISOC_CHANNELS, &reg, sizeof(reg), 0);
	if (err < 0)
		return err;

	// Always use the maximum number of data channels in data block of
	// packet.
	reg = cpu_to_le32(flag);
	return snd_fw_transaction(ff->unit, TCODE_WRITE_QUADLET_REQUEST,
				  LATTER_ISOC_START, &reg, sizeof(reg), 0);
}