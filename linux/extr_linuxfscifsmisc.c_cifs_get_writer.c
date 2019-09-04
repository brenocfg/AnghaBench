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
struct cifsInodeInfo {scalar_t__ writers; int /*<<< orphan*/  writers_lock; int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  CIFS_INODE_PENDING_OPLOCK_BREAK ; 
 int /*<<< orphan*/  CIFS_INODE_PENDING_WRITERS ; 
 int /*<<< orphan*/  TASK_KILLABLE ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int wait_on_bit (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wake_up_bit (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

int cifs_get_writer(struct cifsInodeInfo *cinode)
{
	int rc;

start:
	rc = wait_on_bit(&cinode->flags, CIFS_INODE_PENDING_OPLOCK_BREAK,
			 TASK_KILLABLE);
	if (rc)
		return rc;

	spin_lock(&cinode->writers_lock);
	if (!cinode->writers)
		set_bit(CIFS_INODE_PENDING_WRITERS, &cinode->flags);
	cinode->writers++;
	/* Check to see if we have started servicing an oplock break */
	if (test_bit(CIFS_INODE_PENDING_OPLOCK_BREAK, &cinode->flags)) {
		cinode->writers--;
		if (cinode->writers == 0) {
			clear_bit(CIFS_INODE_PENDING_WRITERS, &cinode->flags);
			wake_up_bit(&cinode->flags, CIFS_INODE_PENDING_WRITERS);
		}
		spin_unlock(&cinode->writers_lock);
		goto start;
	}
	spin_unlock(&cinode->writers_lock);
	return 0;
}