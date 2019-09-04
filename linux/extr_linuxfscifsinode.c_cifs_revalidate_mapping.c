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
struct inode {int dummy; } ;
struct TYPE_2__ {unsigned long flags; } ;

/* Variables and functions */
 TYPE_1__* CIFS_I (struct inode*) ; 
 int /*<<< orphan*/  CIFS_INO_INVALID_MAPPING ; 
 int /*<<< orphan*/  CIFS_INO_LOCK ; 
 int /*<<< orphan*/  TASK_KILLABLE ; 
 int cifs_invalidate_mapping (struct inode*) ; 
 int /*<<< orphan*/  cifs_wait_bit_killable ; 
 int /*<<< orphan*/  clear_bit_unlock (int /*<<< orphan*/ ,unsigned long*) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,unsigned long*) ; 
 int /*<<< orphan*/  smp_mb__after_atomic () ; 
 scalar_t__ test_and_clear_bit (int /*<<< orphan*/ ,unsigned long*) ; 
 int wait_on_bit_lock_action (unsigned long*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wake_up_bit (unsigned long*,int /*<<< orphan*/ ) ; 

int
cifs_revalidate_mapping(struct inode *inode)
{
	int rc;
	unsigned long *flags = &CIFS_I(inode)->flags;

	rc = wait_on_bit_lock_action(flags, CIFS_INO_LOCK, cifs_wait_bit_killable,
				     TASK_KILLABLE);
	if (rc)
		return rc;

	if (test_and_clear_bit(CIFS_INO_INVALID_MAPPING, flags)) {
		rc = cifs_invalidate_mapping(inode);
		if (rc)
			set_bit(CIFS_INO_INVALID_MAPPING, flags);
	}

	clear_bit_unlock(CIFS_INO_LOCK, flags);
	smp_mb__after_atomic();
	wake_up_bit(flags, CIFS_INO_LOCK);

	return rc;
}