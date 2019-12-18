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
typedef  int u32 ;
struct rpc_message {struct nfs4_server_caps_res* rpc_resp; struct nfs4_server_caps_arg* rpc_argp; int /*<<< orphan*/ * rpc_proc; } ;
struct nfs_server {int* attr_bitmask; int caps; int* attr_bitmask_nl; int* cache_consistency_bitmask; int* exclcreat_bitmask; int acl_bitmask; int /*<<< orphan*/  fh_expire_type; int /*<<< orphan*/  client; TYPE_1__* nfs_client; } ;
struct nfs_fh {int dummy; } ;
struct nfs4_server_caps_res {int* attr_bitmask; int acl_bitmask; scalar_t__ has_links; scalar_t__ has_symlinks; int* exclcreat_bitmask; int /*<<< orphan*/  fh_expire_type; int /*<<< orphan*/  seq_res; } ;
struct nfs4_server_caps_arg {int* bitmask; int /*<<< orphan*/  seq_args; struct nfs_fh* fhandle; } ;
struct TYPE_2__ {int cl_minorversion; } ;

/* Variables and functions */
 int ACL4_SUPPORT_ALLOW_ACL ; 
 int ARRAY_SIZE (int*) ; 
 int FATTR4_WORD0_ACL ; 
 int FATTR4_WORD0_ACLSUPPORT ; 
 int FATTR4_WORD0_CHANGE ; 
 int FATTR4_WORD0_FH_EXPIRE_TYPE ; 
 int FATTR4_WORD0_FILEID ; 
 int FATTR4_WORD0_LINK_SUPPORT ; 
 int FATTR4_WORD0_SIZE ; 
 int FATTR4_WORD0_SUPPORTED_ATTRS ; 
 int FATTR4_WORD0_SYMLINK_SUPPORT ; 
 int FATTR4_WORD1_MODE ; 
 int FATTR4_WORD1_NFS40_MASK ; 
 int FATTR4_WORD1_NUMLINKS ; 
 int FATTR4_WORD1_OWNER ; 
 int FATTR4_WORD1_OWNER_GROUP ; 
 int FATTR4_WORD1_TIME_ACCESS ; 
 int FATTR4_WORD1_TIME_METADATA ; 
 int FATTR4_WORD1_TIME_MODIFY ; 
 int FATTR4_WORD2_NFS41_MASK ; 
 int FATTR4_WORD2_NFS42_MASK ; 
 int FATTR4_WORD2_SECURITY_LABEL ; 
 int FATTR4_WORD2_SUPPATTR_EXCLCREAT ; 
 size_t NFSPROC4_CLNT_SERVER_CAPS ; 
 int NFS_CAP_ACLS ; 
 int NFS_CAP_ATIME ; 
 int NFS_CAP_CTIME ; 
 int NFS_CAP_FILEID ; 
 int NFS_CAP_HARDLINKS ; 
 int NFS_CAP_MODE ; 
 int NFS_CAP_MTIME ; 
 int NFS_CAP_NLINK ; 
 int NFS_CAP_OWNER ; 
 int NFS_CAP_OWNER_GROUP ; 
 int NFS_CAP_SECURITY_LABEL ; 
 int NFS_CAP_SYMLINKS ; 
 int /*<<< orphan*/  memcpy (int*,int*,int) ; 
 int nfs4_call_sync (int /*<<< orphan*/ ,struct nfs_server*,struct rpc_message*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * nfs4_procedures ; 

__attribute__((used)) static int _nfs4_server_capabilities(struct nfs_server *server, struct nfs_fh *fhandle)
{
	u32 bitmask[3] = {}, minorversion = server->nfs_client->cl_minorversion;
	struct nfs4_server_caps_arg args = {
		.fhandle = fhandle,
		.bitmask = bitmask,
	};
	struct nfs4_server_caps_res res = {};
	struct rpc_message msg = {
		.rpc_proc = &nfs4_procedures[NFSPROC4_CLNT_SERVER_CAPS],
		.rpc_argp = &args,
		.rpc_resp = &res,
	};
	int status;
	int i;

	bitmask[0] = FATTR4_WORD0_SUPPORTED_ATTRS |
		     FATTR4_WORD0_FH_EXPIRE_TYPE |
		     FATTR4_WORD0_LINK_SUPPORT |
		     FATTR4_WORD0_SYMLINK_SUPPORT |
		     FATTR4_WORD0_ACLSUPPORT;
	if (minorversion)
		bitmask[2] = FATTR4_WORD2_SUPPATTR_EXCLCREAT;

	status = nfs4_call_sync(server->client, server, &msg, &args.seq_args, &res.seq_res, 0);
	if (status == 0) {
		/* Sanity check the server answers */
		switch (minorversion) {
		case 0:
			res.attr_bitmask[1] &= FATTR4_WORD1_NFS40_MASK;
			res.attr_bitmask[2] = 0;
			break;
		case 1:
			res.attr_bitmask[2] &= FATTR4_WORD2_NFS41_MASK;
			break;
		case 2:
			res.attr_bitmask[2] &= FATTR4_WORD2_NFS42_MASK;
		}
		memcpy(server->attr_bitmask, res.attr_bitmask, sizeof(server->attr_bitmask));
		server->caps &= ~(NFS_CAP_ACLS|NFS_CAP_HARDLINKS|
				NFS_CAP_SYMLINKS|NFS_CAP_FILEID|
				NFS_CAP_MODE|NFS_CAP_NLINK|NFS_CAP_OWNER|
				NFS_CAP_OWNER_GROUP|NFS_CAP_ATIME|
				NFS_CAP_CTIME|NFS_CAP_MTIME|
				NFS_CAP_SECURITY_LABEL);
		if (res.attr_bitmask[0] & FATTR4_WORD0_ACL &&
				res.acl_bitmask & ACL4_SUPPORT_ALLOW_ACL)
			server->caps |= NFS_CAP_ACLS;
		if (res.has_links != 0)
			server->caps |= NFS_CAP_HARDLINKS;
		if (res.has_symlinks != 0)
			server->caps |= NFS_CAP_SYMLINKS;
		if (res.attr_bitmask[0] & FATTR4_WORD0_FILEID)
			server->caps |= NFS_CAP_FILEID;
		if (res.attr_bitmask[1] & FATTR4_WORD1_MODE)
			server->caps |= NFS_CAP_MODE;
		if (res.attr_bitmask[1] & FATTR4_WORD1_NUMLINKS)
			server->caps |= NFS_CAP_NLINK;
		if (res.attr_bitmask[1] & FATTR4_WORD1_OWNER)
			server->caps |= NFS_CAP_OWNER;
		if (res.attr_bitmask[1] & FATTR4_WORD1_OWNER_GROUP)
			server->caps |= NFS_CAP_OWNER_GROUP;
		if (res.attr_bitmask[1] & FATTR4_WORD1_TIME_ACCESS)
			server->caps |= NFS_CAP_ATIME;
		if (res.attr_bitmask[1] & FATTR4_WORD1_TIME_METADATA)
			server->caps |= NFS_CAP_CTIME;
		if (res.attr_bitmask[1] & FATTR4_WORD1_TIME_MODIFY)
			server->caps |= NFS_CAP_MTIME;
#ifdef CONFIG_NFS_V4_SECURITY_LABEL
		if (res.attr_bitmask[2] & FATTR4_WORD2_SECURITY_LABEL)
			server->caps |= NFS_CAP_SECURITY_LABEL;
#endif
		memcpy(server->attr_bitmask_nl, res.attr_bitmask,
				sizeof(server->attr_bitmask));
		server->attr_bitmask_nl[2] &= ~FATTR4_WORD2_SECURITY_LABEL;

		memcpy(server->cache_consistency_bitmask, res.attr_bitmask, sizeof(server->cache_consistency_bitmask));
		server->cache_consistency_bitmask[0] &= FATTR4_WORD0_CHANGE|FATTR4_WORD0_SIZE;
		server->cache_consistency_bitmask[1] &= FATTR4_WORD1_TIME_METADATA|FATTR4_WORD1_TIME_MODIFY;
		server->cache_consistency_bitmask[2] = 0;

		/* Avoid a regression due to buggy server */
		for (i = 0; i < ARRAY_SIZE(res.exclcreat_bitmask); i++)
			res.exclcreat_bitmask[i] &= res.attr_bitmask[i];
		memcpy(server->exclcreat_bitmask, res.exclcreat_bitmask,
			sizeof(server->exclcreat_bitmask));

		server->acl_bitmask = res.acl_bitmask;
		server->fh_expire_type = res.fh_expire_type;
	}

	return status;
}