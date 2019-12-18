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
struct cred {int dummy; } ;

/* Variables and functions */
 int nfs_do_access (struct inode*,struct cred const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nfs_open_permission_mask (int) ; 

int nfs_may_open(struct inode *inode, const struct cred *cred, int openflags)
{
	return nfs_do_access(inode, cred, nfs_open_permission_mask(openflags));
}