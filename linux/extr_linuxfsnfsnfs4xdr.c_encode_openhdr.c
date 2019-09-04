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
struct TYPE_4__ {int uniquifier; int /*<<< orphan*/  create_time; } ;
struct nfs_openargs {TYPE_2__ id; TYPE_1__* server; int /*<<< orphan*/  clientid; int /*<<< orphan*/  share_access; int /*<<< orphan*/  seqid; } ;
typedef  int /*<<< orphan*/  __be32 ;
struct TYPE_3__ {int s_dev; } ;

/* Variables and functions */
 void* cpu_to_be32 (int) ; 
 int /*<<< orphan*/  encode_nfs4_seqid (struct xdr_stream*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  encode_share_access (struct xdr_stream*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * reserve_space (struct xdr_stream*,int) ; 
 int /*<<< orphan*/ * xdr_encode_hyper (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * xdr_encode_opaque_fixed (int /*<<< orphan*/ *,char*,int) ; 

__attribute__((used)) static inline void encode_openhdr(struct xdr_stream *xdr, const struct nfs_openargs *arg)
{
	__be32 *p;
 /*
 * opcode 4, seqid 4, share_access 4, share_deny 4, clientid 8, ownerlen 4,
 * owner 4 = 32
 */
	encode_nfs4_seqid(xdr, arg->seqid);
	encode_share_access(xdr, arg->share_access);
	p = reserve_space(xdr, 36);
	p = xdr_encode_hyper(p, arg->clientid);
	*p++ = cpu_to_be32(24);
	p = xdr_encode_opaque_fixed(p, "open id:", 8);
	*p++ = cpu_to_be32(arg->server->s_dev);
	*p++ = cpu_to_be32(arg->id.uniquifier);
	xdr_encode_hyper(p, arg->id.create_time);
}