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
struct vx_core {int chip_status; int /*<<< orphan*/  lock; TYPE_1__* ops; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* change_audio_source ) (struct vx_core*,int) ;} ;

/* Variables and functions */
 int VX_STAT_IS_STALE ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (struct vx_core*,int) ; 

__attribute__((used)) static void vx_change_audio_source(struct vx_core *chip, int src)
{
	if (chip->chip_status & VX_STAT_IS_STALE)
		return;

	mutex_lock(&chip->lock);
	chip->ops->change_audio_source(chip, src);
	mutex_unlock(&chip->lock);
}