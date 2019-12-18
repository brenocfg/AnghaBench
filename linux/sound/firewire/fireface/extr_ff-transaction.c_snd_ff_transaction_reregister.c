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
struct TYPE_4__ {int offset; } ;
struct snd_ff {TYPE_2__* spec; int /*<<< orphan*/  unit; TYPE_1__ async_handler; } ;
struct fw_card {int node_id; } ;
typedef  int /*<<< orphan*/  reg ;
typedef  int /*<<< orphan*/  __le32 ;
struct TYPE_6__ {struct fw_card* card; } ;
struct TYPE_5__ {int /*<<< orphan*/  midi_high_addr; } ;

/* Variables and functions */
 int /*<<< orphan*/  TCODE_WRITE_QUADLET_REQUEST ; 
 int /*<<< orphan*/  cpu_to_le32 (int) ; 
 TYPE_3__* fw_parent_device (int /*<<< orphan*/ ) ; 
 int snd_fw_transaction (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 

int snd_ff_transaction_reregister(struct snd_ff *ff)
{
	struct fw_card *fw_card = fw_parent_device(ff->unit)->card;
	u32 addr;
	__le32 reg;

	/*
	 * Controllers are allowed to register its node ID and upper 2 byte of
	 * local address to listen asynchronous transactions.
	 */
	addr = (fw_card->node_id << 16) | (ff->async_handler.offset >> 32);
	reg = cpu_to_le32(addr);
	return snd_fw_transaction(ff->unit, TCODE_WRITE_QUADLET_REQUEST,
				  ff->spec->midi_high_addr,
				  &reg, sizeof(reg), 0);
}