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
struct inode {int /*<<< orphan*/  i_data; int /*<<< orphan*/  i_lru; int /*<<< orphan*/  i_wb_list; int /*<<< orphan*/  i_io_list; int /*<<< orphan*/  i_devices; int /*<<< orphan*/  i_hash; } ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_HLIST_NODE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  __address_space_init_once (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  i_size_ordered_init (struct inode*) ; 
 int /*<<< orphan*/  memset (struct inode*,int /*<<< orphan*/ ,int) ; 

void inode_init_once(struct inode *inode)
{
	memset(inode, 0, sizeof(*inode));
	INIT_HLIST_NODE(&inode->i_hash);
	INIT_LIST_HEAD(&inode->i_devices);
	INIT_LIST_HEAD(&inode->i_io_list);
	INIT_LIST_HEAD(&inode->i_wb_list);
	INIT_LIST_HEAD(&inode->i_lru);
	__address_space_init_once(&inode->i_data);
	i_size_ordered_init(inode);
}