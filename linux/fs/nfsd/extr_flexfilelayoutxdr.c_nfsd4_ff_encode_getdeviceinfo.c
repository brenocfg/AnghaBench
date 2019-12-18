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
struct xdr_stream {int dummy; } ;
struct TYPE_2__ {int netid_len; int addr_len; int /*<<< orphan*/  addr; int /*<<< orphan*/  netid; } ;
struct pnfs_ff_device_addr {int version; int minor_version; int rsize; int wsize; int tightly_coupled; TYPE_1__ netaddr; } ;
struct nfsd4_getdeviceinfo {struct pnfs_ff_device_addr* gd_device; } ;
typedef  int /*<<< orphan*/  __be32 ;

/* Variables and functions */
 void* cpu_to_be32 (int) ; 
 int /*<<< orphan*/  nfserr_resource ; 
 int /*<<< orphan*/ * xdr_encode_opaque (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/ * xdr_reserve_space (struct xdr_stream*,int) ; 

__be32
nfsd4_ff_encode_getdeviceinfo(struct xdr_stream *xdr,
		struct nfsd4_getdeviceinfo *gdp)
{
	struct pnfs_ff_device_addr *da = gdp->gd_device;
	int len;
	int ver_len;
	int addr_len;
	__be32 *p;

	/* len + padding for two strings */
	addr_len = 16 + da->netaddr.netid_len + da->netaddr.addr_len;
	ver_len = 20;

	len = 4 + ver_len + 4 + addr_len;

	p = xdr_reserve_space(xdr, len + sizeof(__be32));
	if (!p)
		return nfserr_resource;

	/*
	 * Fill in the overall length and number of volumes at the beginning
	 * of the layout.
	 */
	*p++ = cpu_to_be32(len);
	*p++ = cpu_to_be32(1);			/* 1 netaddr */
	p = xdr_encode_opaque(p, da->netaddr.netid, da->netaddr.netid_len);
	p = xdr_encode_opaque(p, da->netaddr.addr, da->netaddr.addr_len);

	*p++ = cpu_to_be32(1);			/* 1 versions */

	*p++ = cpu_to_be32(da->version);
	*p++ = cpu_to_be32(da->minor_version);
	*p++ = cpu_to_be32(da->rsize);
	*p++ = cpu_to_be32(da->wsize);
	*p++ = cpu_to_be32(da->tightly_coupled);

	return 0;
}