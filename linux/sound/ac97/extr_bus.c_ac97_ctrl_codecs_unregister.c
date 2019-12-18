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
struct ac97_controller {TYPE_1__** codecs; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; int /*<<< orphan*/ * ac97_ctrl; } ;

/* Variables and functions */
 int AC97_BUS_MAX_CODECS ; 
 int /*<<< orphan*/  ac97_unbound_ctrl ; 
 int /*<<< orphan*/  device_unregister (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void ac97_ctrl_codecs_unregister(struct ac97_controller *ac97_ctrl)
{
	int i;

	for (i = 0; i < AC97_BUS_MAX_CODECS; i++)
		if (ac97_ctrl->codecs[i]) {
			ac97_ctrl->codecs[i]->ac97_ctrl = &ac97_unbound_ctrl;
			device_unregister(&ac97_ctrl->codecs[i]->dev);
		}
}