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
struct xdr_stream {scalar_t__ p; } ;
struct svc_rqst {int dummy; } ;
struct cb_getattrres {scalar_t__ status; int /*<<< orphan*/  mtime; int /*<<< orphan*/  bitmap; int /*<<< orphan*/  ctime; int /*<<< orphan*/  size; int /*<<< orphan*/  change_attr; } ;
typedef  scalar_t__ __be32 ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NFS4ERR_RESOURCE ; 
 scalar_t__ cpu_to_be32 (int /*<<< orphan*/ ) ; 
 scalar_t__ encode_attr_bitmap (struct xdr_stream*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ encode_attr_change (struct xdr_stream*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ encode_attr_ctime (struct xdr_stream*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ encode_attr_mtime (struct xdr_stream*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ encode_attr_size (struct xdr_stream*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ htonl (unsigned int) ; 
 scalar_t__ unlikely (int) ; 
 scalar_t__* xdr_reserve_space (struct xdr_stream*,int) ; 

__attribute__((used)) static __be32 encode_getattr_res(struct svc_rqst *rqstp, struct xdr_stream *xdr,
		const void *resp)
{
	const struct cb_getattrres *res = resp;
	__be32 *savep = NULL;
	__be32 status = res->status;
	
	if (unlikely(status != 0))
		goto out;
	status = encode_attr_bitmap(xdr, res->bitmap, ARRAY_SIZE(res->bitmap));
	if (unlikely(status != 0))
		goto out;
	status = cpu_to_be32(NFS4ERR_RESOURCE);
	savep = xdr_reserve_space(xdr, sizeof(*savep));
	if (unlikely(!savep))
		goto out;
	status = encode_attr_change(xdr, res->bitmap, res->change_attr);
	if (unlikely(status != 0))
		goto out;
	status = encode_attr_size(xdr, res->bitmap, res->size);
	if (unlikely(status != 0))
		goto out;
	status = encode_attr_ctime(xdr, res->bitmap, &res->ctime);
	if (unlikely(status != 0))
		goto out;
	status = encode_attr_mtime(xdr, res->bitmap, &res->mtime);
	*savep = htonl((unsigned int)((char *)xdr->p - (char *)(savep+1)));
out:
	return status;
}