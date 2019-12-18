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
struct file {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  i_data; scalar_t__ i_mapping; } ;

/* Variables and functions */
 int /*<<< orphan*/  GOSSIP_FILE_DEBUG ; 
 int /*<<< orphan*/  GOSSIP_INODE_DEBUG ; 
 int ORANGEFS_FEATURE_READAHEAD ; 
 TYPE_1__* file_inode (struct file*) ; 
 int /*<<< orphan*/  flush_racache (struct inode*) ; 
 int /*<<< orphan*/  get_khandle_from_ino (struct inode*) ; 
 int /*<<< orphan*/  gossip_debug (int /*<<< orphan*/ ,char*,...) ; 
 scalar_t__ mapping_nrpages (int /*<<< orphan*/ *) ; 
 int orangefs_features ; 

__attribute__((used)) static int orangefs_file_release(struct inode *inode, struct file *file)
{
	gossip_debug(GOSSIP_FILE_DEBUG,
		     "orangefs_file_release: called on %pD\n",
		     file);

	/*
	 * remove all associated inode pages from the page cache and
	 * readahead cache (if any); this forces an expensive refresh of
	 * data for the next caller of mmap (or 'get_block' accesses)
	 */
	if (file_inode(file) &&
	    file_inode(file)->i_mapping &&
	    mapping_nrpages(&file_inode(file)->i_data)) {
		if (orangefs_features & ORANGEFS_FEATURE_READAHEAD) {
			gossip_debug(GOSSIP_INODE_DEBUG,
			    "calling flush_racache on %pU\n",
			    get_khandle_from_ino(inode));
			flush_racache(inode);
			gossip_debug(GOSSIP_INODE_DEBUG,
			    "flush_racache finished\n");
		}

	}
	return 0;
}