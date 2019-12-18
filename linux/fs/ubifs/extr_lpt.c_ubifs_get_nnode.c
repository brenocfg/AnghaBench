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
struct ubifs_nnode {struct ubifs_nbranch* nbranch; } ;
struct ubifs_nbranch {struct ubifs_nnode* nnode; } ;
struct ubifs_info {int dummy; } ;

/* Variables and functions */
 struct ubifs_nnode* ERR_PTR (int) ; 
 int ubifs_read_nnode (struct ubifs_info*,struct ubifs_nnode*,int) ; 

struct ubifs_nnode *ubifs_get_nnode(struct ubifs_info *c,
				    struct ubifs_nnode *parent, int iip)
{
	struct ubifs_nbranch *branch;
	struct ubifs_nnode *nnode;
	int err;

	branch = &parent->nbranch[iip];
	nnode = branch->nnode;
	if (nnode)
		return nnode;
	err = ubifs_read_nnode(c, parent, iip);
	if (err)
		return ERR_PTR(err);
	return branch->nnode;
}