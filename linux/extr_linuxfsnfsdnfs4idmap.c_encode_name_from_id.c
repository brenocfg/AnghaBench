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
typedef  int /*<<< orphan*/  u32 ;
struct xdr_stream {int dummy; } ;
struct TYPE_2__ {scalar_t__ cr_flavor; } ;
struct svc_rqst {TYPE_1__ rq_cred; } ;
typedef  int /*<<< orphan*/  __be32 ;

/* Variables and functions */
 scalar_t__ RPC_AUTH_GSS ; 
 int /*<<< orphan*/  encode_ascii_id (struct xdr_stream*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  idmap_id_to_name (struct xdr_stream*,struct svc_rqst*,int,int /*<<< orphan*/ ) ; 
 scalar_t__ nfs4_disable_idmapping ; 

__attribute__((used)) static __be32 encode_name_from_id(struct xdr_stream *xdr,
				  struct svc_rqst *rqstp, int type, u32 id)
{
	if (nfs4_disable_idmapping && rqstp->rq_cred.cr_flavor < RPC_AUTH_GSS)
		return encode_ascii_id(xdr, id);
	return idmap_id_to_name(xdr, rqstp, type, id);
}