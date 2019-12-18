#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct snd_oxfw {int /*<<< orphan*/  dwork; int /*<<< orphan*/  hwdep_wait; int /*<<< orphan*/  lock; int /*<<< orphan*/  mutex; struct ieee1394_device_id const* entry; int /*<<< orphan*/  unit; } ;
struct ieee1394_device_id {scalar_t__ vendor_id; } ;
struct fw_unit {int /*<<< orphan*/  device; } ;

/* Variables and functions */
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_DEFERRABLE_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ VENDOR_LOUD ; 
 int /*<<< orphan*/  detect_loud_models (struct fw_unit*) ; 
 int /*<<< orphan*/  dev_set_drvdata (int /*<<< orphan*/ *,struct snd_oxfw*) ; 
 struct snd_oxfw* devm_kzalloc (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  do_registration ; 
 int /*<<< orphan*/  fw_unit_get (struct fw_unit*) ; 
 int /*<<< orphan*/  init_waitqueue_head (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  snd_fw_schedule_registration (struct fw_unit*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int oxfw_probe(struct fw_unit *unit,
		      const struct ieee1394_device_id *entry)
{
	struct snd_oxfw *oxfw;

	if (entry->vendor_id == VENDOR_LOUD && !detect_loud_models(unit))
		return -ENODEV;

	/* Allocate this independent of sound card instance. */
	oxfw = devm_kzalloc(&unit->device, sizeof(struct snd_oxfw), GFP_KERNEL);
	if (!oxfw)
		return -ENOMEM;
	oxfw->unit = fw_unit_get(unit);
	dev_set_drvdata(&unit->device, oxfw);

	oxfw->entry = entry;
	mutex_init(&oxfw->mutex);
	spin_lock_init(&oxfw->lock);
	init_waitqueue_head(&oxfw->hwdep_wait);

	/* Allocate and register this sound card later. */
	INIT_DEFERRABLE_WORK(&oxfw->dwork, do_registration);
	snd_fw_schedule_registration(unit, &oxfw->dwork);

	return 0;
}