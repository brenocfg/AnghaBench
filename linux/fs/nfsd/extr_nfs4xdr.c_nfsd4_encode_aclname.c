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
struct svc_rqst {int dummy; } ;
struct nfs4_ace {scalar_t__ whotype; int flag; int /*<<< orphan*/  who_uid; int /*<<< orphan*/  who_gid; } ;
typedef  int /*<<< orphan*/  __be32 ;

/* Variables and functions */
 int NFS4_ACE_IDENTIFIER_GROUP ; 
 scalar_t__ NFS4_ACL_WHO_NAMED ; 
 int /*<<< orphan*/  nfs4_acl_write_who (struct xdr_stream*,scalar_t__) ; 
 int /*<<< orphan*/  nfsd4_encode_group (struct xdr_stream*,struct svc_rqst*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nfsd4_encode_user (struct xdr_stream*,struct svc_rqst*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline __be32
nfsd4_encode_aclname(struct xdr_stream *xdr, struct svc_rqst *rqstp,
		     struct nfs4_ace *ace)
{
	if (ace->whotype != NFS4_ACL_WHO_NAMED)
		return nfs4_acl_write_who(xdr, ace->whotype);
	else if (ace->flag & NFS4_ACE_IDENTIFIER_GROUP)
		return nfsd4_encode_group(xdr, rqstp, ace->who_gid);
	else
		return nfsd4_encode_user(xdr, rqstp, ace->who_uid);
}