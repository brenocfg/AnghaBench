#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int length; struct snd_tscm* callback_data; int /*<<< orphan*/  address_callback; } ;
struct snd_tscm {TYPE_2__ async_handler; TYPE_1__* out_ports; int /*<<< orphan*/  unit; } ;
struct fw_address_region {int start; int end; } ;
struct TYPE_4__ {int /*<<< orphan*/  work; scalar_t__ next_ktime; int /*<<< orphan*/  parent; } ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 unsigned int TSCM_MIDI_OUT_PORT_MAX ; 
 int fw_core_add_address_handler (TYPE_2__*,struct fw_address_region const*) ; 
 int /*<<< orphan*/  fw_core_remove_address_handler (TYPE_2__*) ; 
 int /*<<< orphan*/  fw_parent_device (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  handle_midi_tx ; 
 int /*<<< orphan*/  midi_port_work ; 
 int snd_tscm_transaction_reregister (struct snd_tscm*) ; 

int snd_tscm_transaction_register(struct snd_tscm *tscm)
{
	static const struct fw_address_region resp_register_region = {
		.start	= 0xffffe0000000ull,
		.end	= 0xffffe000ffffull,
	};
	unsigned int i;
	int err;

	/*
	 * Usually, two quadlets are transferred by one transaction. The first
	 * quadlet has MIDI messages, the rest includes timestamp.
	 * Sometimes, 8 set of the data is transferred by a block transaction.
	 */
	tscm->async_handler.length = 8 * 8;
	tscm->async_handler.address_callback = handle_midi_tx;
	tscm->async_handler.callback_data = tscm;

	err = fw_core_add_address_handler(&tscm->async_handler,
					  &resp_register_region);
	if (err < 0)
		return err;

	err = snd_tscm_transaction_reregister(tscm);
	if (err < 0)
		goto error;

	for (i = 0; i < TSCM_MIDI_OUT_PORT_MAX; i++) {
		tscm->out_ports[i].parent = fw_parent_device(tscm->unit);
		tscm->out_ports[i].next_ktime = 0;
		INIT_WORK(&tscm->out_ports[i].work, midi_port_work);
	}

	return err;
error:
	fw_core_remove_address_handler(&tscm->async_handler);
	tscm->async_handler.callback_data = NULL;
	return err;
}