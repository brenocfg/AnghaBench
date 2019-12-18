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
struct snd_tscm {int /*<<< orphan*/  dwork; int /*<<< orphan*/  hwdep_wait; int /*<<< orphan*/  lock; int /*<<< orphan*/  mutex; int /*<<< orphan*/  unit; } ;
struct ieee1394_device_id {int dummy; } ;
struct fw_unit {int /*<<< orphan*/  device; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_DEFERRABLE_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_set_drvdata (int /*<<< orphan*/ *,struct snd_tscm*) ; 
 struct snd_tscm* devm_kzalloc (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  do_registration ; 
 int /*<<< orphan*/  fw_unit_get (struct fw_unit*) ; 
 int /*<<< orphan*/  init_waitqueue_head (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  snd_fw_schedule_registration (struct fw_unit*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int snd_tscm_probe(struct fw_unit *unit,
			   const struct ieee1394_device_id *entry)
{
	struct snd_tscm *tscm;

	/* Allocate this independent of sound card instance. */
	tscm = devm_kzalloc(&unit->device, sizeof(struct snd_tscm), GFP_KERNEL);
	if (!tscm)
		return -ENOMEM;
	tscm->unit = fw_unit_get(unit);
	dev_set_drvdata(&unit->device, tscm);

	mutex_init(&tscm->mutex);
	spin_lock_init(&tscm->lock);
	init_waitqueue_head(&tscm->hwdep_wait);

	/* Allocate and register this sound card later. */
	INIT_DEFERRABLE_WORK(&tscm->dwork, do_registration);
	snd_fw_schedule_registration(unit, &tscm->dwork);

	return 0;
}