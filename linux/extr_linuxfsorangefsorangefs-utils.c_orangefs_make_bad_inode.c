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
struct inode {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  GOSSIP_UTILS_DEBUG ; 
 int /*<<< orphan*/  get_khandle_from_ino (struct inode*) ; 
 int /*<<< orphan*/  gossip_debug (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 scalar_t__ is_root_handle (struct inode*) ; 
 int /*<<< orphan*/  make_bad_inode (struct inode*) ; 

__attribute__((used)) static void orangefs_make_bad_inode(struct inode *inode)
{
	if (is_root_handle(inode)) {
		/*
		 * if this occurs, the pvfs2-client-core was killed but we
		 * can't afford to lose the inode operations and such
		 * associated with the root handle in any case.
		 */
		gossip_debug(GOSSIP_UTILS_DEBUG,
			     "*** NOT making bad root inode %pU\n",
			     get_khandle_from_ino(inode));
	} else {
		gossip_debug(GOSSIP_UTILS_DEBUG,
			     "*** making bad inode %pU\n",
			     get_khandle_from_ino(inode));
		make_bad_inode(inode);
	}
}