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
typedef  int /*<<< orphan*/  nfs4_stateid ;
typedef  int /*<<< orphan*/  __be32 ;

/* Variables and functions */
 int /*<<< orphan*/  NFS4_OPEN_CLAIM_DELEG_CUR_FH ; 
 int /*<<< orphan*/  cpu_to_be32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  encode_nfs4_stateid (struct xdr_stream*,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/ * reserve_space (struct xdr_stream*,int) ; 

__attribute__((used)) static inline void encode_claim_delegate_cur_fh(struct xdr_stream *xdr, const nfs4_stateid *stateid)
{
	__be32 *p;

	p = reserve_space(xdr, 4);
	*p = cpu_to_be32(NFS4_OPEN_CLAIM_DELEG_CUR_FH);
	encode_nfs4_stateid(xdr, stateid);
}