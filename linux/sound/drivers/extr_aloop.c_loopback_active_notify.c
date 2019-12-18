#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct loopback_pcm {TYPE_1__* loopback; } ;
struct TYPE_4__ {int /*<<< orphan*/  active_id; } ;
struct TYPE_3__ {int /*<<< orphan*/  card; } ;

/* Variables and functions */
 int /*<<< orphan*/  SNDRV_CTL_EVENT_MASK_VALUE ; 
 TYPE_2__* get_setup (struct loopback_pcm*) ; 
 int /*<<< orphan*/  snd_ctl_notify (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void loopback_active_notify(struct loopback_pcm *dpcm)
{
	snd_ctl_notify(dpcm->loopback->card,
		       SNDRV_CTL_EVENT_MASK_VALUE,
		       &get_setup(dpcm)->active_id);
}