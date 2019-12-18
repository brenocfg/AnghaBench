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
struct inode {int /*<<< orphan*/  i_lock; } ;
struct cifsInodeInfo {scalar_t__ time; } ;
typedef  int /*<<< orphan*/  loff_t ;

/* Variables and functions */
 struct cifsInodeInfo* CIFS_I (struct inode*) ; 
 int /*<<< orphan*/  i_size_write (struct inode*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  truncate_pagecache (struct inode*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void cifs_setsize(struct inode *inode, loff_t offset)
{
	struct cifsInodeInfo *cifs_i = CIFS_I(inode);

	spin_lock(&inode->i_lock);
	i_size_write(inode, offset);
	spin_unlock(&inode->i_lock);

	/* Cached inode must be refreshed on truncate */
	cifs_i->time = 0;
	truncate_pagecache(inode, offset);
}