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
struct nfs_pgio_header {int /*<<< orphan*/  inode; int /*<<< orphan*/  cred; } ;
struct nfs_pageio_descriptor {int pg_error; int /*<<< orphan*/  pg_ioflags; int /*<<< orphan*/  pg_rpc_callops; int /*<<< orphan*/  pg_rw_ops; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  NFS_CLIENT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NFS_PROTO (int /*<<< orphan*/ ) ; 
 int nfs_generic_pgio (struct nfs_pageio_descriptor*,struct nfs_pgio_header*) ; 
 int nfs_initiate_pgio (int /*<<< orphan*/ ,struct nfs_pgio_header*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nfs_pgheader_init (struct nfs_pageio_descriptor*,struct nfs_pgio_header*,int /*<<< orphan*/ ) ; 
 struct nfs_pgio_header* nfs_pgio_header_alloc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nfs_pgio_header_free ; 

__attribute__((used)) static int nfs_generic_pg_pgios(struct nfs_pageio_descriptor *desc)
{
	struct nfs_pgio_header *hdr;
	int ret;

	hdr = nfs_pgio_header_alloc(desc->pg_rw_ops);
	if (!hdr) {
		desc->pg_error = -ENOMEM;
		return desc->pg_error;
	}
	nfs_pgheader_init(desc, hdr, nfs_pgio_header_free);
	ret = nfs_generic_pgio(desc, hdr);
	if (ret == 0)
		ret = nfs_initiate_pgio(NFS_CLIENT(hdr->inode),
					hdr,
					hdr->cred,
					NFS_PROTO(hdr->inode),
					desc->pg_rpc_callops,
					desc->pg_ioflags, 0);
	return ret;
}