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
struct snd_oxfw {int dev_lock_changed; int /*<<< orphan*/  hwdep_wait; } ;

/* Variables and functions */
 int /*<<< orphan*/  wake_up (int /*<<< orphan*/ *) ; 

void snd_oxfw_stream_lock_changed(struct snd_oxfw *oxfw)
{
	oxfw->dev_lock_changed = true;
	wake_up(&oxfw->hwdep_wait);
}