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
struct nfs_fattr {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_NOFS ; 
 struct nfs_fattr* kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nfs_fattr_init (struct nfs_fattr*) ; 

struct nfs_fattr *nfs_alloc_fattr(void)
{
	struct nfs_fattr *fattr;

	fattr = kmalloc(sizeof(*fattr), GFP_NOFS);
	if (fattr != NULL)
		nfs_fattr_init(fattr);
	return fattr;
}