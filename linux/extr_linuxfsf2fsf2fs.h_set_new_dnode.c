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
struct page {int dummy; } ;
struct inode {int dummy; } ;
struct dnode_of_data {int /*<<< orphan*/  nid; struct page* node_page; struct page* inode_page; struct inode* inode; } ;
typedef  int /*<<< orphan*/  nid_t ;

/* Variables and functions */
 int /*<<< orphan*/  memset (struct dnode_of_data*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static inline void set_new_dnode(struct dnode_of_data *dn, struct inode *inode,
		struct page *ipage, struct page *npage, nid_t nid)
{
	memset(dn, 0, sizeof(*dn));
	dn->inode = inode;
	dn->inode_page = ipage;
	dn->node_page = npage;
	dn->nid = nid;
}