#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct xdr_stream {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  si_opaque; int /*<<< orphan*/  si_generation; } ;
typedef  TYPE_1__ stateid_t ;
typedef  int /*<<< orphan*/  __be32 ;

/* Variables and functions */
 int /*<<< orphan*/  NFS4_STATEID_OTHER_SIZE ; 
 int /*<<< orphan*/  NFS4_STATEID_SIZE ; 
 int /*<<< orphan*/  cpu_to_be32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xdr_encode_opaque_fixed (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * xdr_reserve_space (struct xdr_stream*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void encode_stateid4(struct xdr_stream *xdr, const stateid_t *sid)
{
	__be32 *p;

	p = xdr_reserve_space(xdr, NFS4_STATEID_SIZE);
	*p++ = cpu_to_be32(sid->si_generation);
	xdr_encode_opaque_fixed(p, &sid->si_opaque, NFS4_STATEID_OTHER_SIZE);
}