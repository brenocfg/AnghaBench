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
struct snd_ff_spec {int dummy; } ;
struct snd_ff {int /*<<< orphan*/  dwork; struct snd_ff_spec const* spec; int /*<<< orphan*/  hwdep_wait; int /*<<< orphan*/  lock; int /*<<< orphan*/  mutex; int /*<<< orphan*/  unit; } ;
struct ieee1394_device_id {scalar_t__ driver_data; } ;
struct fw_unit {int /*<<< orphan*/  device; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_DEFERRABLE_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_set_drvdata (int /*<<< orphan*/ *,struct snd_ff*) ; 
 struct snd_ff* devm_kzalloc (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  do_registration ; 
 int /*<<< orphan*/  fw_unit_get (struct fw_unit*) ; 
 int /*<<< orphan*/  init_waitqueue_head (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  snd_fw_schedule_registration (struct fw_unit*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int snd_ff_probe(struct fw_unit *unit,
			   const struct ieee1394_device_id *entry)
{
	struct snd_ff *ff;

	ff = devm_kzalloc(&unit->device, sizeof(struct snd_ff), GFP_KERNEL);
	if (!ff)
		return -ENOMEM;
	ff->unit = fw_unit_get(unit);
	dev_set_drvdata(&unit->device, ff);

	mutex_init(&ff->mutex);
	spin_lock_init(&ff->lock);
	init_waitqueue_head(&ff->hwdep_wait);

	ff->spec = (const struct snd_ff_spec *)entry->driver_data;

	/* Register this sound card later. */
	INIT_DEFERRABLE_WORK(&ff->dwork, do_registration);
	snd_fw_schedule_registration(unit, &ff->dwork);

	return 0;
}