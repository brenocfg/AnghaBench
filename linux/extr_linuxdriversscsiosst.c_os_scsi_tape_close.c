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
struct osst_tape {scalar_t__ door_locked; int /*<<< orphan*/  device; scalar_t__ in_use; int /*<<< orphan*/  buffer; scalar_t__ header_ok; scalar_t__ raw; } ;
struct inode {int dummy; } ;
struct file {struct osst_tape* private_data; } ;

/* Variables and functions */
 scalar_t__ ST_LOCKED_AUTO ; 
 int /*<<< orphan*/  do_door_lock (struct osst_tape*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  normalize_buffer (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  os_scsi_tapes_lock ; 
 int /*<<< orphan*/  scsi_device_put (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  write_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  write_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int os_scsi_tape_close(struct inode * inode, struct file * filp)
{
	int		      result = 0;
	struct osst_tape    * STp    = filp->private_data;

	if (STp->door_locked == ST_LOCKED_AUTO)
		do_door_lock(STp, 0);

	if (STp->raw)
		STp->header_ok = 0;
	
	normalize_buffer(STp->buffer);
	write_lock(&os_scsi_tapes_lock);
	STp->in_use = 0;
	write_unlock(&os_scsi_tapes_lock);

	scsi_device_put(STp->device);

	return result;
}