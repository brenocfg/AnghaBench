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
struct xdr_stream {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  len; int /*<<< orphan*/  data; } ;
struct nfs4_stateowner {TYPE_2__ so_owner; TYPE_1__* so_client; } ;
typedef  int /*<<< orphan*/  __be32 ;
struct TYPE_3__ {int /*<<< orphan*/  cl_clientid; } ;

/* Variables and functions */
 int /*<<< orphan*/  xdr_encode_opaque (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * xdr_encode_opaque_fixed (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/ * xdr_reserve_space (struct xdr_stream*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void encode_stateowner(struct xdr_stream *xdr, struct nfs4_stateowner *so)
{
	__be32	*p;

	p = xdr_reserve_space(xdr, 8 + 4 + so->so_owner.len);
	p = xdr_encode_opaque_fixed(p, &so->so_client->cl_clientid, 8);
	xdr_encode_opaque(p, so->so_owner.data, so->so_owner.len);
}