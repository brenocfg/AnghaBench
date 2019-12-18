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
struct snd_oxfw {int wrong_dbs; scalar_t__ midi_output_ports; scalar_t__ midi_input_ports; TYPE_1__* entry; int /*<<< orphan*/  unit; } ;
struct fw_device {scalar_t__ config_rom; } ;
struct fw_csr_iterator {int dummy; } ;
struct TYPE_2__ {scalar_t__ vendor_id; } ;

/* Variables and functions */
 int CSR_MODEL ; 
 int CSR_VENDOR ; 
 int MODEL_SATELLITE ; 
 scalar_t__ OUI_STANTON ; 
 scalar_t__ VENDOR_GRIFFIN ; 
 scalar_t__ VENDOR_LACIE ; 
 int VENDOR_LOUD ; 
 scalar_t__ VENDOR_TASCAM ; 
 int /*<<< orphan*/  fw_csr_iterator_init (struct fw_csr_iterator*,scalar_t__) ; 
 scalar_t__ fw_csr_iterator_next (struct fw_csr_iterator*,int*,int*) ; 
 struct fw_device* fw_parent_device (int /*<<< orphan*/ ) ; 
 int snd_oxfw_add_spkr (struct snd_oxfw*,int) ; 
 int snd_oxfw_scs1x_add (struct snd_oxfw*) ; 

__attribute__((used)) static int detect_quirks(struct snd_oxfw *oxfw)
{
	struct fw_device *fw_dev = fw_parent_device(oxfw->unit);
	struct fw_csr_iterator it;
	int key, val;
	int vendor, model;

	/*
	 * Add ALSA control elements for two models to keep compatibility to
	 * old firewire-speaker module.
	 */
	if (oxfw->entry->vendor_id == VENDOR_GRIFFIN)
		return snd_oxfw_add_spkr(oxfw, false);
	if (oxfw->entry->vendor_id == VENDOR_LACIE)
		return snd_oxfw_add_spkr(oxfw, true);

	/*
	 * Stanton models supports asynchronous transactions for unique MIDI
	 * messages.
	 */
	if (oxfw->entry->vendor_id == OUI_STANTON) {
		/* No physical MIDI ports. */
		oxfw->midi_input_ports = 0;
		oxfw->midi_output_ports = 0;

		return snd_oxfw_scs1x_add(oxfw);
	}

	/*
	 * TASCAM FireOne has physical control and requires a pair of additional
	 * MIDI ports.
	 */
	if (oxfw->entry->vendor_id == VENDOR_TASCAM) {
		oxfw->midi_input_ports++;
		oxfw->midi_output_ports++;
		return 0;
	}

	/* Seek from Root Directory of Config ROM. */
	vendor = model = 0;
	fw_csr_iterator_init(&it, fw_dev->config_rom + 5);
	while (fw_csr_iterator_next(&it, &key, &val)) {
		if (key == CSR_VENDOR)
			vendor = val;
		else if (key == CSR_MODEL)
			model = val;
	}

	/*
	 * Mackie Onyx Satellite with base station has a quirk to report a wrong
	 * value in 'dbs' field of CIP header against its format information.
	 */
	if (vendor == VENDOR_LOUD && model == MODEL_SATELLITE)
		oxfw->wrong_dbs = true;

	return 0;
}