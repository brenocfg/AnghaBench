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
struct pnfs_block_deviceaddr {int nr_volumes; int /*<<< orphan*/ * volumes; } ;
struct nfsd4_getdeviceinfo {struct pnfs_block_deviceaddr* gd_device; } ;
typedef  int /*<<< orphan*/  __be32 ;

/* Variables and functions */
 void* cpu_to_be32 (int) ; 
 int nfsd4_block_encode_volume (struct xdr_stream*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nfserr_resource ; 
 int /*<<< orphan*/  nfserrno (int) ; 
 int /*<<< orphan*/ * xdr_reserve_space (struct xdr_stream*,int) ; 

__be32
nfsd4_block_encode_getdeviceinfo(struct xdr_stream *xdr,
		struct nfsd4_getdeviceinfo *gdp)
{
	struct pnfs_block_deviceaddr *dev = gdp->gd_device;
	int len = sizeof(__be32), ret, i;
	__be32 *p;

	p = xdr_reserve_space(xdr, len + sizeof(__be32));
	if (!p)
		return nfserr_resource;

	for (i = 0; i < dev->nr_volumes; i++) {
		ret = nfsd4_block_encode_volume(xdr, &dev->volumes[i]);
		if (ret < 0)
			return nfserrno(ret);
		len += ret;
	}

	/*
	 * Fill in the overall length and number of volumes at the beginning
	 * of the layout.
	 */
	*p++ = cpu_to_be32(len);
	*p++ = cpu_to_be32(dev->nr_volumes);
	return 0;
}