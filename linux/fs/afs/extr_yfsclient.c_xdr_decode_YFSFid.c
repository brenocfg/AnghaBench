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
struct TYPE_2__ {int /*<<< orphan*/  unique; int /*<<< orphan*/  hi; int /*<<< orphan*/  lo; } ;
struct yfs_xdr_YFSFid {TYPE_1__ vnode; int /*<<< orphan*/  volume; } ;
struct afs_fid {void* unique; void* vnode_hi; void* vnode; void* vid; } ;
typedef  int /*<<< orphan*/  __be32 ;

/* Variables and functions */
 void* ntohl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xdr_size (struct yfs_xdr_YFSFid const*) ; 
 void* xdr_to_u64 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void xdr_decode_YFSFid(const __be32 **_bp, struct afs_fid *fid)
{
	const struct yfs_xdr_YFSFid *x = (const void *)*_bp;

	fid->vid	= xdr_to_u64(x->volume);
	fid->vnode	= xdr_to_u64(x->vnode.lo);
	fid->vnode_hi	= ntohl(x->vnode.hi);
	fid->unique	= ntohl(x->vnode.unique);
	*_bp += xdr_size(x);
}