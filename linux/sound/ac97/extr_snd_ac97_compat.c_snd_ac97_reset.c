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
struct snd_ac97 {int /*<<< orphan*/  private_data; } ;
struct ac97_controller {int dummy; } ;
struct ac97_codec_device {int /*<<< orphan*/  vendor_id; int /*<<< orphan*/  num; struct ac97_controller* ac97_ctrl; } ;

/* Variables and functions */
 int ENODEV ; 
 scalar_t__ ac97_ids_match (unsigned int,int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  compat_ac97_reset (struct snd_ac97*) ; 
 int /*<<< orphan*/  compat_ac97_warm_reset (struct snd_ac97*) ; 
 unsigned int snd_ac97_bus_scan_one (struct ac97_controller*,int /*<<< orphan*/ ) ; 
 struct ac97_codec_device* to_ac97_device (int /*<<< orphan*/ ) ; 

int snd_ac97_reset(struct snd_ac97 *ac97, bool try_warm, unsigned int id,
	unsigned int id_mask)
{
	struct ac97_codec_device *adev = to_ac97_device(ac97->private_data);
	struct ac97_controller *actrl = adev->ac97_ctrl;
	unsigned int scanned;

	if (try_warm) {
		compat_ac97_warm_reset(ac97);
		scanned = snd_ac97_bus_scan_one(actrl, adev->num);
		if (ac97_ids_match(scanned, adev->vendor_id, id_mask))
			return 1;
	}

	compat_ac97_reset(ac97);
	compat_ac97_warm_reset(ac97);
	scanned = snd_ac97_bus_scan_one(actrl, adev->num);
	if (ac97_ids_match(scanned, adev->vendor_id, id_mask))
		return 0;

	return -ENODEV;
}