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
struct timespec64 {int dummy; } ;
struct inode {int dummy; } ;
struct iattr {int /*<<< orphan*/  ia_valid; } ;

/* Variables and functions */
 int /*<<< orphan*/  ATTR_ATIME ; 
 int /*<<< orphan*/  ATTR_CTIME ; 
 int /*<<< orphan*/  ATTR_MTIME ; 
 int /*<<< orphan*/  GOSSIP_INODE_DEBUG ; 
 int S_ATIME ; 
 int S_CTIME ; 
 int S_MTIME ; 
 int __orangefs_setattr (struct inode*,struct iattr*) ; 
 int /*<<< orphan*/  generic_update_time (struct inode*,struct timespec64*,int) ; 
 int /*<<< orphan*/  get_khandle_from_ino (struct inode*) ; 
 int /*<<< orphan*/  gossip_debug (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct iattr*,int /*<<< orphan*/ ,int) ; 

int orangefs_update_time(struct inode *inode, struct timespec64 *time, int flags)
{
	struct iattr iattr;
	gossip_debug(GOSSIP_INODE_DEBUG, "orangefs_update_time: %pU\n",
	    get_khandle_from_ino(inode));
	generic_update_time(inode, time, flags);
	memset(&iattr, 0, sizeof iattr);
        if (flags & S_ATIME)
		iattr.ia_valid |= ATTR_ATIME;
	if (flags & S_CTIME)
		iattr.ia_valid |= ATTR_CTIME;
	if (flags & S_MTIME)
		iattr.ia_valid |= ATTR_MTIME;
	return __orangefs_setattr(inode, &iattr);
}