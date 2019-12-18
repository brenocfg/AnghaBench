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
struct snd_motu_spec {int dummy; } ;
struct snd_motu {int /*<<< orphan*/  dwork; int /*<<< orphan*/  hwdep_wait; int /*<<< orphan*/  lock; int /*<<< orphan*/  mutex; struct snd_motu_spec const* spec; int /*<<< orphan*/  unit; } ;
struct ieee1394_device_id {scalar_t__ driver_data; } ;
struct fw_unit {int /*<<< orphan*/  device; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_DEFERRABLE_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_set_drvdata (int /*<<< orphan*/ *,struct snd_motu*) ; 
 struct snd_motu* devm_kzalloc (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  do_registration ; 
 int /*<<< orphan*/  fw_unit_get (struct fw_unit*) ; 
 int /*<<< orphan*/  init_waitqueue_head (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  snd_fw_schedule_registration (struct fw_unit*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int motu_probe(struct fw_unit *unit,
		      const struct ieee1394_device_id *entry)
{
	struct snd_motu *motu;

	/* Allocate this independently of sound card instance. */
	motu = devm_kzalloc(&unit->device, sizeof(struct snd_motu), GFP_KERNEL);
	if (!motu)
		return -ENOMEM;
	motu->unit = fw_unit_get(unit);
	dev_set_drvdata(&unit->device, motu);

	motu->spec = (const struct snd_motu_spec *)entry->driver_data;
	mutex_init(&motu->mutex);
	spin_lock_init(&motu->lock);
	init_waitqueue_head(&motu->hwdep_wait);

	/* Allocate and register this sound card later. */
	INIT_DEFERRABLE_WORK(&motu->dwork, do_registration);
	snd_fw_schedule_registration(unit, &motu->dwork);

	return 0;
}