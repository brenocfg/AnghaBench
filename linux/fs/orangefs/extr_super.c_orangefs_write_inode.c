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
struct writeback_control {int dummy; } ;
struct inode {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  GOSSIP_SUPER_DEBUG ; 
 int /*<<< orphan*/  gossip_debug (int /*<<< orphan*/ ,char*) ; 
 int orangefs_inode_setattr (struct inode*) ; 

__attribute__((used)) static int orangefs_write_inode(struct inode *inode,
				struct writeback_control *wbc)
{
	gossip_debug(GOSSIP_SUPER_DEBUG, "orangefs_write_inode\n");
	return orangefs_inode_setattr(inode);
}