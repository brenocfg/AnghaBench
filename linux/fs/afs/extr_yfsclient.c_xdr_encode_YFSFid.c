#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {void* unique; void* hi; void* lo; } ;
struct yfs_xdr_YFSFid {TYPE_1__ vnode; void* volume; } ;
struct afs_fid {int /*<<< orphan*/  unique; int /*<<< orphan*/  vnode_hi; int /*<<< orphan*/  vnode; int /*<<< orphan*/  vid; } ;
typedef  int /*<<< orphan*/  __be32 ;

/* Variables and functions */
 void* htonl (int /*<<< orphan*/ ) ; 
 void* u64_to_xdr (int /*<<< orphan*/ ) ; 
 int xdr_size (struct yfs_xdr_YFSFid*) ; 

__attribute__((used)) static __be32 *xdr_encode_YFSFid(__be32 *bp, struct afs_fid *fid)
{
	struct yfs_xdr_YFSFid *x = (void *)bp;

	x->volume	= u64_to_xdr(fid->vid);
	x->vnode.lo	= u64_to_xdr(fid->vnode);
	x->vnode.hi	= htonl(fid->vnode_hi);
	x->vnode.unique	= htonl(fid->unique);
	return bp + xdr_size(x);
}