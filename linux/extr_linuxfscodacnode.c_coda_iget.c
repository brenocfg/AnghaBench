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
struct super_block {int dummy; } ;
struct inode {int i_state; unsigned long i_ino; } ;
struct coda_vattr {int dummy; } ;
struct coda_inode_info {scalar_t__ c_mapcount; } ;
struct CodaFid {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENOMEM ; 
 struct inode* ERR_PTR (int /*<<< orphan*/ ) ; 
 struct coda_inode_info* ITOC (struct inode*) ; 
 int I_NEW ; 
 unsigned long coda_f2i (struct CodaFid*) ; 
 int /*<<< orphan*/  coda_fill_inode (struct inode*,struct coda_vattr*) ; 
 int /*<<< orphan*/  coda_set_inode ; 
 int /*<<< orphan*/  coda_test_inode ; 
 struct inode* iget5_locked (struct super_block*,unsigned long,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct CodaFid*) ; 
 int /*<<< orphan*/  unlock_new_inode (struct inode*) ; 

struct inode * coda_iget(struct super_block * sb, struct CodaFid * fid,
			 struct coda_vattr * attr)
{
	struct inode *inode;
	struct coda_inode_info *cii;
	unsigned long hash = coda_f2i(fid);

	inode = iget5_locked(sb, hash, coda_test_inode, coda_set_inode, fid);

	if (!inode)
		return ERR_PTR(-ENOMEM);

	if (inode->i_state & I_NEW) {
		cii = ITOC(inode);
		/* we still need to set i_ino for things like stat(2) */
		inode->i_ino = hash;
		/* inode is locked and unique, no need to grab cii->c_lock */
		cii->c_mapcount = 0;
		unlock_new_inode(inode);
	}

	/* always replace the attributes, type might have changed */
	coda_fill_inode(inode, attr);
	return inode;
}