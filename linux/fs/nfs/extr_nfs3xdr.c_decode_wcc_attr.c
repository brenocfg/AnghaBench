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
struct xdr_stream {int dummy; } ;
struct nfs_fattr {int valid; int /*<<< orphan*/  pre_ctime; int /*<<< orphan*/  pre_change_attr; int /*<<< orphan*/  pre_mtime; int /*<<< orphan*/  pre_size; } ;
typedef  int /*<<< orphan*/  __be32 ;

/* Variables and functions */
 int EIO ; 
 int NFS3_wcc_attr_sz ; 
 int NFS_ATTR_FATTR_PRECHANGE ; 
 int NFS_ATTR_FATTR_PRECTIME ; 
 int NFS_ATTR_FATTR_PREMTIME ; 
 int NFS_ATTR_FATTR_PRESIZE ; 
 int /*<<< orphan*/  nfs_timespec_to_change_attr (int /*<<< orphan*/ *) ; 
 scalar_t__ unlikely (int) ; 
 int /*<<< orphan*/ * xdr_decode_nfstime3 (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * xdr_decode_size3 (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * xdr_inline_decode (struct xdr_stream*,int) ; 

__attribute__((used)) static int decode_wcc_attr(struct xdr_stream *xdr, struct nfs_fattr *fattr)
{
	__be32 *p;

	p = xdr_inline_decode(xdr, NFS3_wcc_attr_sz << 2);
	if (unlikely(!p))
		return -EIO;

	fattr->valid |= NFS_ATTR_FATTR_PRESIZE
		| NFS_ATTR_FATTR_PRECHANGE
		| NFS_ATTR_FATTR_PREMTIME
		| NFS_ATTR_FATTR_PRECTIME;

	p = xdr_decode_size3(p, &fattr->pre_size);
	p = xdr_decode_nfstime3(p, &fattr->pre_mtime);
	xdr_decode_nfstime3(p, &fattr->pre_ctime);
	fattr->pre_change_attr = nfs_timespec_to_change_attr(&fattr->pre_ctime);

	return 0;
}