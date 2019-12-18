#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_8__ ;
typedef  struct TYPE_15__   TYPE_7__ ;
typedef  struct TYPE_14__   TYPE_6__ ;
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct super_block {struct nfs_server* s_fs_info; } ;
struct nfs_server {int flags; unsigned int acregmin; unsigned int acregmax; unsigned int acdirmin; unsigned int acdirmax; TYPE_6__* nfs_client; int /*<<< orphan*/  port; TYPE_4__* client; int /*<<< orphan*/  wsize; int /*<<< orphan*/  rsize; } ;
struct TYPE_15__ {int /*<<< orphan*/  addrlen; int /*<<< orphan*/  address; int /*<<< orphan*/  port; } ;
struct nfs_parsed_mount_data {int flags; unsigned int acregmin; unsigned int acregmax; unsigned int acdirmin; unsigned int acdirmax; unsigned int timeo; int version; int /*<<< orphan*/  lsm_opts; TYPE_7__ nfs_server; int /*<<< orphan*/  net; int /*<<< orphan*/  minorversion; int /*<<< orphan*/  selected_flavor; int /*<<< orphan*/  retrans; int /*<<< orphan*/  wsize; int /*<<< orphan*/  rsize; } ;
struct nfs_mount_data {int version; } ;
struct nfs4_mount_data {int version; } ;
struct TYPE_16__ {TYPE_5__* nsproxy; } ;
struct TYPE_14__ {int /*<<< orphan*/  cl_addr; int /*<<< orphan*/  cl_minorversion; int /*<<< orphan*/  cl_addrlen; TYPE_1__* rpc_ops; } ;
struct TYPE_13__ {int /*<<< orphan*/  net_ns; } ;
struct TYPE_12__ {TYPE_3__* cl_timeout; TYPE_2__* cl_auth; } ;
struct TYPE_11__ {unsigned int to_initval; int /*<<< orphan*/  to_retries; } ;
struct TYPE_10__ {int /*<<< orphan*/  au_flavor; } ;
struct TYPE_9__ {int version; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 unsigned int HZ ; 
 int NFS_MOUNT_NOAC ; 
 int SB_SYNCHRONOUS ; 
 TYPE_8__* current ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct nfs_parsed_mount_data* nfs_alloc_parsed_mount_data () ; 
 int nfs_compare_remount_data (struct nfs_server*,struct nfs_parsed_mount_data*) ; 
 int /*<<< orphan*/  nfs_free_parsed_mount_data (struct nfs_parsed_mount_data*) ; 
 int /*<<< orphan*/  nfs_parse_mount_options (char*,struct nfs_parsed_mount_data*) ; 
 int security_sb_remount (struct super_block*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sync_filesystem (struct super_block*) ; 

int
nfs_remount(struct super_block *sb, int *flags, char *raw_data)
{
	int error;
	struct nfs_server *nfss = sb->s_fs_info;
	struct nfs_parsed_mount_data *data;
	struct nfs_mount_data *options = (struct nfs_mount_data *)raw_data;
	struct nfs4_mount_data *options4 = (struct nfs4_mount_data *)raw_data;
	u32 nfsvers = nfss->nfs_client->rpc_ops->version;

	sync_filesystem(sb);

	/*
	 * Userspace mount programs that send binary options generally send
	 * them populated with default values. We have no way to know which
	 * ones were explicitly specified. Fall back to legacy behavior and
	 * just return success.
	 */
	if ((nfsvers == 4 && (!options4 || options4->version == 1)) ||
	    (nfsvers <= 3 && (!options || (options->version >= 1 &&
					   options->version <= 6))))
		return 0;

	data = nfs_alloc_parsed_mount_data();
	if (data == NULL)
		return -ENOMEM;

	/* fill out struct with values from existing mount */
	data->flags = nfss->flags;
	data->rsize = nfss->rsize;
	data->wsize = nfss->wsize;
	data->retrans = nfss->client->cl_timeout->to_retries;
	data->selected_flavor = nfss->client->cl_auth->au_flavor;
	data->acregmin = nfss->acregmin / HZ;
	data->acregmax = nfss->acregmax / HZ;
	data->acdirmin = nfss->acdirmin / HZ;
	data->acdirmax = nfss->acdirmax / HZ;
	data->timeo = 10U * nfss->client->cl_timeout->to_initval / HZ;
	data->nfs_server.port = nfss->port;
	data->nfs_server.addrlen = nfss->nfs_client->cl_addrlen;
	data->version = nfsvers;
	data->minorversion = nfss->nfs_client->cl_minorversion;
	data->net = current->nsproxy->net_ns;
	memcpy(&data->nfs_server.address, &nfss->nfs_client->cl_addr,
		data->nfs_server.addrlen);

	/* overwrite those values with any that were specified */
	error = -EINVAL;
	if (!nfs_parse_mount_options((char *)options, data))
		goto out;

	/*
	 * noac is a special case. It implies -o sync, but that's not
	 * necessarily reflected in the mtab options. do_remount_sb
	 * will clear SB_SYNCHRONOUS if -o sync wasn't specified in the
	 * remount options, so we have to explicitly reset it.
	 */
	if (data->flags & NFS_MOUNT_NOAC)
		*flags |= SB_SYNCHRONOUS;

	/* compare new mount options with old ones */
	error = nfs_compare_remount_data(nfss, data);
	if (!error)
		error = security_sb_remount(sb, data->lsm_opts);
out:
	nfs_free_parsed_mount_data(data);
	return error;
}