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
struct ac97_controller {void** codecs_pdata; } ;
struct ac97_codec_device {size_t num; struct ac97_controller* ac97_ctrl; } ;

/* Variables and functions */

void *snd_ac97_codec_get_platdata(const struct ac97_codec_device *adev)
{
	struct ac97_controller *ac97_ctrl = adev->ac97_ctrl;

	return ac97_ctrl->codecs_pdata[adev->num];
}