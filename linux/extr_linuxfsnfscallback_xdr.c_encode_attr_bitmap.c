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
typedef  int /*<<< orphan*/  uint32_t ;
struct xdr_stream {int dummy; } ;
typedef  int /*<<< orphan*/  __be32 ;

/* Variables and functions */
 int /*<<< orphan*/  NFS4ERR_RESOURCE ; 
 int /*<<< orphan*/  cpu_to_be32 (int /*<<< orphan*/ ) ; 
 scalar_t__ xdr_stream_encode_uint32_array (struct xdr_stream*,int /*<<< orphan*/  const*,size_t) ; 

__attribute__((used)) static __be32 encode_attr_bitmap(struct xdr_stream *xdr, const uint32_t *bitmap, size_t sz)
{
	if (xdr_stream_encode_uint32_array(xdr, bitmap, sz) < 0)
		return cpu_to_be32(NFS4ERR_RESOURCE);
	return 0;
}