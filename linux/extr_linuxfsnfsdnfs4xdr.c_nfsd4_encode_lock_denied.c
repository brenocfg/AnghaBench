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
typedef  int /*<<< orphan*/  u64 ;
struct xdr_stream {int dummy; } ;
struct xdr_netobj {int /*<<< orphan*/ * data; scalar_t__ len; } ;
struct nfsd4_lock_denied {int /*<<< orphan*/  ld_clientid; int /*<<< orphan*/  ld_type; int /*<<< orphan*/  ld_length; int /*<<< orphan*/  ld_start; struct xdr_netobj ld_owner; } ;
typedef  int /*<<< orphan*/  __be32 ;

/* Variables and functions */
 scalar_t__ XDR_LEN (scalar_t__) ; 
 void* cpu_to_be32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nfserr_denied ; 
 int /*<<< orphan*/  nfserr_resource ; 
 int /*<<< orphan*/ * xdr_encode_hyper (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * xdr_encode_opaque (int /*<<< orphan*/ *,int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/ * xdr_encode_opaque_fixed (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/ * xdr_reserve_space (struct xdr_stream*,scalar_t__) ; 

__attribute__((used)) static __be32
nfsd4_encode_lock_denied(struct xdr_stream *xdr, struct nfsd4_lock_denied *ld)
{
	struct xdr_netobj *conf = &ld->ld_owner;
	__be32 *p;

again:
	p = xdr_reserve_space(xdr, 32 + XDR_LEN(conf->len));
	if (!p) {
		/*
		 * Don't fail to return the result just because we can't
		 * return the conflicting open:
		 */
		if (conf->len) {
			kfree(conf->data);
			conf->len = 0;
			conf->data = NULL;
			goto again;
		}
		return nfserr_resource;
	}
	p = xdr_encode_hyper(p, ld->ld_start);
	p = xdr_encode_hyper(p, ld->ld_length);
	*p++ = cpu_to_be32(ld->ld_type);
	if (conf->len) {
		p = xdr_encode_opaque_fixed(p, &ld->ld_clientid, 8);
		p = xdr_encode_opaque(p, conf->data, conf->len);
		kfree(conf->data);
	}  else {  /* non - nfsv4 lock in conflict, no clientid nor owner */
		p = xdr_encode_hyper(p, (u64)0); /* clientid */
		*p++ = cpu_to_be32(0); /* length of owner name */
	}
	return nfserr_denied;
}