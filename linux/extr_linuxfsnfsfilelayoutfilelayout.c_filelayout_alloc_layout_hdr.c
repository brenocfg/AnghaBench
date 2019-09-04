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
struct pnfs_layout_hdr {int dummy; } ;
struct nfs4_filelayout {struct pnfs_layout_hdr generic_hdr; } ;
struct inode {int dummy; } ;
typedef  int /*<<< orphan*/  gfp_t ;

/* Variables and functions */
 struct nfs4_filelayout* kzalloc (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct pnfs_layout_hdr *
filelayout_alloc_layout_hdr(struct inode *inode, gfp_t gfp_flags)
{
	struct nfs4_filelayout *flo;

	flo = kzalloc(sizeof(*flo), gfp_flags);
	return flo != NULL ? &flo->generic_hdr : NULL;
}