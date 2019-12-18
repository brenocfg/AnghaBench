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
struct TYPE_2__ {int /*<<< orphan*/  data; } ;
struct nfs42_device_error {int /*<<< orphan*/  opnum; int /*<<< orphan*/  status; TYPE_1__ dev_id; } ;
typedef  void* __be32 ;

/* Variables and functions */
 scalar_t__ NFS4_DEVICEID4_SIZE ; 
 void* cpu_to_be32 (int /*<<< orphan*/ ) ; 
 void** reserve_space (struct xdr_stream*,scalar_t__) ; 
 void** xdr_encode_opaque_fixed (void**,int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void encode_device_error(struct xdr_stream *xdr,
				const struct nfs42_device_error *error)
{
	__be32 *p;

	p = reserve_space(xdr, NFS4_DEVICEID4_SIZE + 2*4);
	p = xdr_encode_opaque_fixed(p, error->dev_id.data,
			NFS4_DEVICEID4_SIZE);
	*p++ = cpu_to_be32(error->status);
	*p = cpu_to_be32(error->opnum);
}