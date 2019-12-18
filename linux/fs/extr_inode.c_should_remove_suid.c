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
typedef  int umode_t ;
struct dentry {int dummy; } ;
struct TYPE_2__ {int i_mode; } ;

/* Variables and functions */
 int ATTR_KILL_SGID ; 
 int ATTR_KILL_SUID ; 
 int /*<<< orphan*/  CAP_FSETID ; 
 int S_ISGID ; 
 scalar_t__ S_ISREG (int) ; 
 int S_ISUID ; 
 int S_IXGRP ; 
 int /*<<< orphan*/  capable (int /*<<< orphan*/ ) ; 
 TYPE_1__* d_inode (struct dentry*) ; 
 scalar_t__ unlikely (int) ; 

int should_remove_suid(struct dentry *dentry)
{
	umode_t mode = d_inode(dentry)->i_mode;
	int kill = 0;

	/* suid always must be killed */
	if (unlikely(mode & S_ISUID))
		kill = ATTR_KILL_SUID;

	/*
	 * sgid without any exec bits is just a mandatory locking mark; leave
	 * it alone.  If some exec bits are set, it's a real sgid; kill it.
	 */
	if (unlikely((mode & S_ISGID) && (mode & S_IXGRP)))
		kill |= ATTR_KILL_SGID;

	if (unlikely(kill && !capable(CAP_FSETID) && S_ISREG(mode)))
		return kill;

	return 0;
}