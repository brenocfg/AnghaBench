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
struct scsi_tape {scalar_t__ door_locked; int /*<<< orphan*/  device; scalar_t__ in_use; int /*<<< orphan*/  buffer; } ;
struct inode {int dummy; } ;
struct file {struct scsi_tape* private_data; } ;

/* Variables and functions */
 scalar_t__ ST_LOCKED_AUTO ; 
 int /*<<< orphan*/  do_door_lock (struct scsi_tape*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  normalize_buffer (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  scsi_autopm_put_device (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  scsi_tape_put (struct scsi_tape*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  st_use_lock ; 

__attribute__((used)) static int st_release(struct inode *inode, struct file *filp)
{
	int result = 0;
	struct scsi_tape *STp = filp->private_data;

	if (STp->door_locked == ST_LOCKED_AUTO)
		do_door_lock(STp, 0);

	normalize_buffer(STp->buffer);
	spin_lock(&st_use_lock);
	STp->in_use = 0;
	spin_unlock(&st_use_lock);
	scsi_autopm_put_device(STp->device);
	scsi_tape_put(STp);

	return result;
}