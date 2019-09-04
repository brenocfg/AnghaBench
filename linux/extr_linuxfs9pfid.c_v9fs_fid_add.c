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
struct p9_fid {int dummy; } ;
struct dentry {int /*<<< orphan*/  d_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  __add_fid (struct dentry*,struct p9_fid*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

void v9fs_fid_add(struct dentry *dentry, struct p9_fid *fid)
{
	spin_lock(&dentry->d_lock);
	__add_fid(dentry, fid);
	spin_unlock(&dentry->d_lock);
}