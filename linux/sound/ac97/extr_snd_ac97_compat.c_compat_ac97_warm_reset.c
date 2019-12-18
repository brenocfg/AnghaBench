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
struct snd_ac97 {int /*<<< orphan*/  private_data; } ;
struct ac97_controller {TYPE_1__* ops; } ;
struct ac97_codec_device {struct ac97_controller* ac97_ctrl; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* warm_reset ) (struct ac97_controller*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (struct ac97_controller*) ; 
 struct ac97_codec_device* to_ac97_device (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void compat_ac97_warm_reset(struct snd_ac97 *ac97)
{
	struct ac97_codec_device *adev = to_ac97_device(ac97->private_data);
	struct ac97_controller *actrl = adev->ac97_ctrl;

	if (actrl->ops->warm_reset)
		actrl->ops->warm_reset(actrl);
}