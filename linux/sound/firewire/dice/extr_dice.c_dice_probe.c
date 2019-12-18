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
struct snd_dice {int /*<<< orphan*/  dwork; int /*<<< orphan*/  hwdep_wait; int /*<<< orphan*/  clock_accepted; int /*<<< orphan*/  mutex; int /*<<< orphan*/  lock; scalar_t__ detect_formats; int /*<<< orphan*/  unit; } ;
struct ieee1394_device_id {scalar_t__ vendor_id; scalar_t__ driver_data; } ;
struct fw_unit {int /*<<< orphan*/  device; } ;
typedef  scalar_t__ snd_dice_detect_formats_t ;

/* Variables and functions */
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_DEFERRABLE_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ OUI_SSL ; 
 int check_dice_category (struct fw_unit*) ; 
 int /*<<< orphan*/  dev_set_drvdata (int /*<<< orphan*/ *,struct snd_dice*) ; 
 struct snd_dice* devm_kzalloc (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  do_registration ; 
 int /*<<< orphan*/  fw_unit_get (struct fw_unit*) ; 
 int /*<<< orphan*/  init_completion (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  init_waitqueue_head (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 scalar_t__ snd_dice_stream_detect_current_formats ; 
 int /*<<< orphan*/  snd_fw_schedule_registration (struct fw_unit*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int dice_probe(struct fw_unit *unit,
		      const struct ieee1394_device_id *entry)
{
	struct snd_dice *dice;
	int err;

	if (!entry->driver_data && entry->vendor_id != OUI_SSL) {
		err = check_dice_category(unit);
		if (err < 0)
			return -ENODEV;
	}

	/* Allocate this independent of sound card instance. */
	dice = devm_kzalloc(&unit->device, sizeof(struct snd_dice), GFP_KERNEL);
	if (!dice)
		return -ENOMEM;
	dice->unit = fw_unit_get(unit);
	dev_set_drvdata(&unit->device, dice);

	if (!entry->driver_data) {
		dice->detect_formats = snd_dice_stream_detect_current_formats;
	} else {
		dice->detect_formats =
				(snd_dice_detect_formats_t)entry->driver_data;
	}

	spin_lock_init(&dice->lock);
	mutex_init(&dice->mutex);
	init_completion(&dice->clock_accepted);
	init_waitqueue_head(&dice->hwdep_wait);

	/* Allocate and register this sound card later. */
	INIT_DEFERRABLE_WORK(&dice->dwork, do_registration);
	snd_fw_schedule_registration(unit, &dice->dwork);

	return 0;
}