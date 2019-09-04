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
struct cifsInodeInfo {int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  CIFS_INODE_PENDING_OPLOCK_BREAK ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wake_up_bit (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void cifs_done_oplock_break(struct cifsInodeInfo *cinode)
{
	clear_bit(CIFS_INODE_PENDING_OPLOCK_BREAK, &cinode->flags);
	wake_up_bit(&cinode->flags, CIFS_INODE_PENDING_OPLOCK_BREAK);
}