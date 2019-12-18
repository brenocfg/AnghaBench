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
struct nfs_fh {scalar_t__ size; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_NOFS ; 
 struct nfs_fh* kmalloc (int,int /*<<< orphan*/ ) ; 

struct nfs_fh *nfs_alloc_fhandle(void)
{
	struct nfs_fh *fh;

	fh = kmalloc(sizeof(struct nfs_fh), GFP_NOFS);
	if (fh != NULL)
		fh->size = 0;
	return fh;
}