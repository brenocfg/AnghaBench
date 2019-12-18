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
struct vx_rmh {int dummy; } ;
struct vx_core {int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int vx_send_msg_nolock (struct vx_core*,struct vx_rmh*) ; 

int vx_send_msg(struct vx_core *chip, struct vx_rmh *rmh)
{
	int err;

	mutex_lock(&chip->lock);
	err = vx_send_msg_nolock(chip, rmh);
	mutex_unlock(&chip->lock);
	return err;
}