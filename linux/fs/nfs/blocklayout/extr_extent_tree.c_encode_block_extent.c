#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct pnfs_block_extent {long long be_f_offset; long long be_length; TYPE_2__* be_device; } ;
typedef  int /*<<< orphan*/  __be32 ;
struct TYPE_3__ {int /*<<< orphan*/  data; } ;
struct TYPE_4__ {TYPE_1__ deviceid; } ;

/* Variables and functions */
 int /*<<< orphan*/  NFS4_DEVICEID4_SIZE ; 
 int /*<<< orphan*/  PNFS_BLOCK_READWRITE_DATA ; 
 long long SECTOR_SHIFT ; 
 int /*<<< orphan*/  cpu_to_be32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * xdr_encode_hyper (int /*<<< orphan*/ *,long long) ; 
 int /*<<< orphan*/ * xdr_encode_opaque_fixed (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static __be32 *encode_block_extent(struct pnfs_block_extent *be, __be32 *p)
{
	p = xdr_encode_opaque_fixed(p, be->be_device->deviceid.data,
			NFS4_DEVICEID4_SIZE);
	p = xdr_encode_hyper(p, be->be_f_offset << SECTOR_SHIFT);
	p = xdr_encode_hyper(p, be->be_length << SECTOR_SHIFT);
	p = xdr_encode_hyper(p, 0LL);
	*p++ = cpu_to_be32(PNFS_BLOCK_READWRITE_DATA);
	return p;
}