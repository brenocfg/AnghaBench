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
struct TYPE_4__ {int offset; } ;
struct snd_tscm {int /*<<< orphan*/  unit; TYPE_2__ async_handler; } ;
struct fw_device {TYPE_1__* card; } ;
typedef  int /*<<< orphan*/  reg ;
typedef  int /*<<< orphan*/  __be32 ;
struct TYPE_3__ {int node_id; } ;

/* Variables and functions */
 int /*<<< orphan*/  TCODE_WRITE_QUADLET_REQUEST ; 
 scalar_t__ TSCM_ADDR_BASE ; 
 scalar_t__ TSCM_OFFSET_LED_POWER ; 
 scalar_t__ TSCM_OFFSET_MIDI_TX_ADDR_HI ; 
 scalar_t__ TSCM_OFFSET_MIDI_TX_ADDR_LO ; 
 scalar_t__ TSCM_OFFSET_MIDI_TX_ON ; 
 int /*<<< orphan*/  cpu_to_be32 (int) ; 
 struct fw_device* fw_parent_device (int /*<<< orphan*/ ) ; 
 int snd_fw_transaction (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 

int snd_tscm_transaction_reregister(struct snd_tscm *tscm)
{
	struct fw_device *device = fw_parent_device(tscm->unit);
	__be32 reg;
	int err;

	/* Register messaging address. Block transaction is not allowed. */
	reg = cpu_to_be32((device->card->node_id << 16) |
			  (tscm->async_handler.offset >> 32));
	err = snd_fw_transaction(tscm->unit, TCODE_WRITE_QUADLET_REQUEST,
				 TSCM_ADDR_BASE + TSCM_OFFSET_MIDI_TX_ADDR_HI,
				 &reg, sizeof(reg), 0);
	if (err < 0)
		return err;

	reg = cpu_to_be32(tscm->async_handler.offset);
	err = snd_fw_transaction(tscm->unit, TCODE_WRITE_QUADLET_REQUEST,
				 TSCM_ADDR_BASE + TSCM_OFFSET_MIDI_TX_ADDR_LO,
				 &reg, sizeof(reg), 0);
	if (err < 0)
		return err;

	/* Turn on messaging. */
	reg = cpu_to_be32(0x00000001);
	err = snd_fw_transaction(tscm->unit, TCODE_WRITE_QUADLET_REQUEST,
				  TSCM_ADDR_BASE + TSCM_OFFSET_MIDI_TX_ON,
				  &reg, sizeof(reg), 0);
	if (err < 0)
		return err;

	/* Turn on FireWire LED. */
	reg = cpu_to_be32(0x0001008e);
	return snd_fw_transaction(tscm->unit, TCODE_WRITE_QUADLET_REQUEST,
				  TSCM_ADDR_BASE + TSCM_OFFSET_LED_POWER,
				  &reg, sizeof(reg), 0);
}