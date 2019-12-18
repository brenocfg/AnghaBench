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
struct nfs_pgio_header {int /*<<< orphan*/  lseg; } ;
struct nfs_pageio_descriptor {int pg_error; int /*<<< orphan*/  pg_lseg; int /*<<< orphan*/  pg_rw_ops; } ;

/* Variables and functions */
 int ENOMEM ; 
 int nfs_generic_pgio (struct nfs_pageio_descriptor*,struct nfs_pgio_header*) ; 
 int /*<<< orphan*/  nfs_pgheader_init (struct nfs_pageio_descriptor*,struct nfs_pgio_header*,int /*<<< orphan*/ ) ; 
 struct nfs_pgio_header* nfs_pgio_header_alloc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pnfs_do_read (struct nfs_pageio_descriptor*,struct nfs_pgio_header*) ; 
 int /*<<< orphan*/  pnfs_get_lseg (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pnfs_readhdr_free ; 

int
pnfs_generic_pg_readpages(struct nfs_pageio_descriptor *desc)
{
	struct nfs_pgio_header *hdr;
	int ret;

	hdr = nfs_pgio_header_alloc(desc->pg_rw_ops);
	if (!hdr) {
		desc->pg_error = -ENOMEM;
		return desc->pg_error;
	}
	nfs_pgheader_init(desc, hdr, pnfs_readhdr_free);
	hdr->lseg = pnfs_get_lseg(desc->pg_lseg);
	ret = nfs_generic_pgio(desc, hdr);
	if (!ret)
		pnfs_do_read(desc, hdr);
	return ret;
}