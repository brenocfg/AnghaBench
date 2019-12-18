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
typedef  int u32 ;
struct xdr_stream {int dummy; } ;
struct TYPE_3__ {int len; int /*<<< orphan*/  data; } ;
struct TYPE_4__ {void* service; void* qop; TYPE_1__ oid; } ;
struct nfs4_secinfo4 {TYPE_2__ flavor_info; } ;
typedef  int /*<<< orphan*/  __be32 ;

/* Variables and functions */
 int EINVAL ; 
 int EIO ; 
 int GSS_OID_MAX_LEN ; 
 void* be32_to_cpup (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 scalar_t__ unlikely (int) ; 
 int /*<<< orphan*/ * xdr_inline_decode (struct xdr_stream*,int) ; 

__attribute__((used)) static int decode_secinfo_gss(struct xdr_stream *xdr,
			      struct nfs4_secinfo4 *flavor)
{
	u32 oid_len;
	__be32 *p;

	p = xdr_inline_decode(xdr, 4);
	if (unlikely(!p))
		return -EIO;
	oid_len = be32_to_cpup(p);
	if (oid_len > GSS_OID_MAX_LEN)
		return -EINVAL;

	p = xdr_inline_decode(xdr, oid_len);
	if (unlikely(!p))
		return -EIO;
	memcpy(flavor->flavor_info.oid.data, p, oid_len);
	flavor->flavor_info.oid.len = oid_len;

	p = xdr_inline_decode(xdr, 8);
	if (unlikely(!p))
		return -EIO;
	flavor->flavor_info.qop = be32_to_cpup(p++);
	flavor->flavor_info.service = be32_to_cpup(p);

	return 0;
}