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
struct snd_bebob_spec {int dummy; } ;
struct snd_bebob {int /*<<< orphan*/  unit; int /*<<< orphan*/  dwork; int /*<<< orphan*/  hwdep_wait; int /*<<< orphan*/  lock; int /*<<< orphan*/  mutex; struct snd_bebob_spec const* spec; struct ieee1394_device_id const* entry; } ;
struct ieee1394_device_id {scalar_t__ vendor_id; scalar_t__ model_id; scalar_t__ driver_data; } ;
struct fw_unit {int /*<<< orphan*/  device; } ;
struct TYPE_2__ {int /*<<< orphan*/  card; } ;

/* Variables and functions */
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_DEFERRABLE_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ MODEL_FOCUSRITE_SAFFIRE_BOTH ; 
 scalar_t__ MODEL_MAUDIO_AUDIOPHILE_BOTH ; 
 scalar_t__ MODEL_MAUDIO_FW1814 ; 
 scalar_t__ MODEL_MAUDIO_PROJECTMIX ; 
 scalar_t__ VEN_FOCUSRITE ; 
 scalar_t__ VEN_MAUDIO1 ; 
 scalar_t__ VEN_MAUDIO2 ; 
 int /*<<< orphan*/  check_audiophile_booted (struct fw_unit*) ; 
 int /*<<< orphan*/  dev_set_drvdata (int /*<<< orphan*/ *,struct snd_bebob*) ; 
 struct snd_bebob* devm_kzalloc (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  do_registration ; 
 TYPE_1__* fw_parent_device (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fw_schedule_bus_reset (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  fw_unit_get (struct fw_unit*) ; 
 struct snd_bebob_spec* get_saffire_spec (struct fw_unit*) ; 
 int /*<<< orphan*/  init_waitqueue_head (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int snd_bebob_maudio_load_firmware (struct fw_unit*) ; 
 int /*<<< orphan*/  snd_fw_schedule_registration (struct fw_unit*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
bebob_probe(struct fw_unit *unit, const struct ieee1394_device_id *entry)
{
	struct snd_bebob *bebob;
	const struct snd_bebob_spec *spec;

	if (entry->vendor_id == VEN_FOCUSRITE &&
	    entry->model_id == MODEL_FOCUSRITE_SAFFIRE_BOTH)
		spec = get_saffire_spec(unit);
	else if (entry->vendor_id == VEN_MAUDIO1 &&
		 entry->model_id == MODEL_MAUDIO_AUDIOPHILE_BOTH &&
		 !check_audiophile_booted(unit))
		spec = NULL;
	else
		spec = (const struct snd_bebob_spec *)entry->driver_data;

	if (spec == NULL) {
		if (entry->vendor_id == VEN_MAUDIO1 ||
		    entry->vendor_id == VEN_MAUDIO2)
			return snd_bebob_maudio_load_firmware(unit);
		else
			return -ENODEV;
	}

	/* Allocate this independent of sound card instance. */
	bebob = devm_kzalloc(&unit->device, sizeof(struct snd_bebob),
			     GFP_KERNEL);
	if (!bebob)
		return -ENOMEM;
	bebob->unit = fw_unit_get(unit);
	dev_set_drvdata(&unit->device, bebob);

	bebob->entry = entry;
	bebob->spec = spec;
	mutex_init(&bebob->mutex);
	spin_lock_init(&bebob->lock);
	init_waitqueue_head(&bebob->hwdep_wait);

	/* Allocate and register this sound card later. */
	INIT_DEFERRABLE_WORK(&bebob->dwork, do_registration);

	if (entry->vendor_id != VEN_MAUDIO1 ||
	    (entry->model_id != MODEL_MAUDIO_FW1814 &&
	     entry->model_id != MODEL_MAUDIO_PROJECTMIX)) {
		snd_fw_schedule_registration(unit, &bebob->dwork);
	} else {
		/*
		 * This is a workaround. This bus reset seems to have an effect
		 * to make devices correctly handling transactions. Without
		 * this, the devices have gap_count mismatch. This causes much
		 * failure of transaction.
		 *
		 * Just after registration, user-land application receive
		 * signals from dbus and starts I/Os. To avoid I/Os till the
		 * future bus reset, registration is done in next update().
		 */
		fw_schedule_bus_reset(fw_parent_device(bebob->unit)->card,
				      false, true);
	}

	return 0;
}