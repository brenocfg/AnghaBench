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
struct dnode_of_data {int node_changed; int /*<<< orphan*/  node_page; } ;

/* Variables and functions */
 int /*<<< orphan*/  NODE ; 
 int /*<<< orphan*/  __set_data_blkaddr (struct dnode_of_data*) ; 
 int /*<<< orphan*/  f2fs_wait_on_page_writeback (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 scalar_t__ set_page_dirty (int /*<<< orphan*/ ) ; 

void f2fs_set_data_blkaddr(struct dnode_of_data *dn)
{
	f2fs_wait_on_page_writeback(dn->node_page, NODE, true, true);
	__set_data_blkaddr(dn);
	if (set_page_dirty(dn->node_page))
		dn->node_changed = true;
}