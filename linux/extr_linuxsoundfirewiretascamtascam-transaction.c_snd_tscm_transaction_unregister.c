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
struct TYPE_2__ {int /*<<< orphan*/ * callback_data; } ;
struct snd_tscm {TYPE_1__ async_handler; int /*<<< orphan*/  unit; } ;
typedef  int /*<<< orphan*/  reg ;
typedef  int /*<<< orphan*/  __be32 ;

/* Variables and functions */
 int /*<<< orphan*/  TCODE_WRITE_QUADLET_REQUEST ; 
 scalar_t__ TSCM_ADDR_BASE ; 
 scalar_t__ TSCM_OFFSET_LED_POWER ; 
 scalar_t__ TSCM_OFFSET_MIDI_TX_ADDR_HI ; 
 scalar_t__ TSCM_OFFSET_MIDI_TX_ADDR_LO ; 
 scalar_t__ TSCM_OFFSET_MIDI_TX_ON ; 
 int /*<<< orphan*/  cpu_to_be32 (int) ; 
 int /*<<< orphan*/  fw_core_remove_address_handler (TYPE_1__*) ; 
 int /*<<< orphan*/  snd_fw_transaction (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 

void snd_tscm_transaction_unregister(struct snd_tscm *tscm)
{
	__be32 reg;

	if (tscm->async_handler.callback_data == NULL)
		return;

	/* Turn off FireWire LED. */
	reg = cpu_to_be32(0x0000008e);
	snd_fw_transaction(tscm->unit, TCODE_WRITE_QUADLET_REQUEST,
			   TSCM_ADDR_BASE + TSCM_OFFSET_LED_POWER,
			   &reg, sizeof(reg), 0);

	/* Turn off messaging. */
	reg = cpu_to_be32(0x00000000);
	snd_fw_transaction(tscm->unit, TCODE_WRITE_QUADLET_REQUEST,
			   TSCM_ADDR_BASE + TSCM_OFFSET_MIDI_TX_ON,
			   &reg, sizeof(reg), 0);

	/* Unregister the address. */
	snd_fw_transaction(tscm->unit, TCODE_WRITE_QUADLET_REQUEST,
			   TSCM_ADDR_BASE + TSCM_OFFSET_MIDI_TX_ADDR_HI,
			   &reg, sizeof(reg), 0);
	snd_fw_transaction(tscm->unit, TCODE_WRITE_QUADLET_REQUEST,
			   TSCM_ADDR_BASE + TSCM_OFFSET_MIDI_TX_ADDR_LO,
			   &reg, sizeof(reg), 0);

	fw_core_remove_address_handler(&tscm->async_handler);
	tscm->async_handler.callback_data = NULL;
}