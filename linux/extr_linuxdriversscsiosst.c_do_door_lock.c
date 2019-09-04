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
struct osst_tape {int /*<<< orphan*/  door_locked; int /*<<< orphan*/  device; } ;

/* Variables and functions */
 int /*<<< orphan*/  SCSI_REMOVAL_ALLOW ; 
 int /*<<< orphan*/  SCSI_REMOVAL_PREVENT ; 
 int /*<<< orphan*/  ST_LOCKED_EXPLICIT ; 
 int /*<<< orphan*/  ST_LOCK_FAILS ; 
 int /*<<< orphan*/  ST_UNLOCKED ; 
 int scsi_set_medium_removal (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int do_door_lock(struct osst_tape * STp, int do_lock)
{
	int retval;

#if DEBUG
	printk(OSST_DEB_MSG "%s:D: %socking drive door.\n", tape_name(STp), do_lock ? "L" : "Unl");
#endif

	retval = scsi_set_medium_removal(STp->device,
			do_lock ? SCSI_REMOVAL_PREVENT : SCSI_REMOVAL_ALLOW);
	if (!retval)
		STp->door_locked = do_lock ? ST_LOCKED_EXPLICIT : ST_UNLOCKED;
	else
		STp->door_locked = ST_LOCK_FAILS;
	return retval;
}