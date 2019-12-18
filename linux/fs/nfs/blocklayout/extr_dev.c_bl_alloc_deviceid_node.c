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
struct xdr_buf {int dummy; } ;
struct pnfs_device {int /*<<< orphan*/  dev_id; int /*<<< orphan*/  pglen; int /*<<< orphan*/  pages; } ;
struct pnfs_block_volume {int dummy; } ;
struct nfs4_deviceid_node {int dummy; } ;
struct pnfs_block_dev {struct nfs4_deviceid_node node; } ;
struct page {int dummy; } ;
struct nfs_server {int dummy; } ;
typedef  int /*<<< orphan*/  gfp_t ;
typedef  int /*<<< orphan*/  __be32 ;

/* Variables and functions */
 int /*<<< orphan*/  PAGE_SIZE ; 
 int /*<<< orphan*/  __free_page (struct page*) ; 
 struct page* alloc_page (int /*<<< orphan*/ ) ; 
 int be32_to_cpup (int /*<<< orphan*/ ) ; 
 int bl_parse_deviceid (struct nfs_server*,struct pnfs_block_dev*,struct pnfs_block_volume*,int,int /*<<< orphan*/ ) ; 
 struct pnfs_block_volume* kcalloc (int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct pnfs_block_volume*) ; 
 struct pnfs_block_dev* kzalloc (int,int /*<<< orphan*/ ) ; 
 int nfs4_block_decode_volume (struct xdr_stream*,struct pnfs_block_volume*) ; 
 int /*<<< orphan*/  nfs4_init_deviceid_node (struct nfs4_deviceid_node*,struct nfs_server*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nfs4_mark_deviceid_unavailable (struct nfs4_deviceid_node*) ; 
 int /*<<< orphan*/  page_address (struct page*) ; 
 int /*<<< orphan*/  xdr_init_decode_pages (struct xdr_stream*,struct xdr_buf*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * xdr_inline_decode (struct xdr_stream*,int) ; 
 int /*<<< orphan*/  xdr_set_scratch_buffer (struct xdr_stream*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

struct nfs4_deviceid_node *
bl_alloc_deviceid_node(struct nfs_server *server, struct pnfs_device *pdev,
		gfp_t gfp_mask)
{
	struct nfs4_deviceid_node *node = NULL;
	struct pnfs_block_volume *volumes;
	struct pnfs_block_dev *top;
	struct xdr_stream xdr;
	struct xdr_buf buf;
	struct page *scratch;
	int nr_volumes, ret, i;
	__be32 *p;

	scratch = alloc_page(gfp_mask);
	if (!scratch)
		goto out;

	xdr_init_decode_pages(&xdr, &buf, pdev->pages, pdev->pglen);
	xdr_set_scratch_buffer(&xdr, page_address(scratch), PAGE_SIZE);

	p = xdr_inline_decode(&xdr, sizeof(__be32));
	if (!p)
		goto out_free_scratch;
	nr_volumes = be32_to_cpup(p++);

	volumes = kcalloc(nr_volumes, sizeof(struct pnfs_block_volume),
			  gfp_mask);
	if (!volumes)
		goto out_free_scratch;

	for (i = 0; i < nr_volumes; i++) {
		ret = nfs4_block_decode_volume(&xdr, &volumes[i]);
		if (ret < 0)
			goto out_free_volumes;
	}

	top = kzalloc(sizeof(*top), gfp_mask);
	if (!top)
		goto out_free_volumes;

	ret = bl_parse_deviceid(server, top, volumes, nr_volumes - 1, gfp_mask);

	node = &top->node;
	nfs4_init_deviceid_node(node, server, &pdev->dev_id);
	if (ret)
		nfs4_mark_deviceid_unavailable(node);

out_free_volumes:
	kfree(volumes);
out_free_scratch:
	__free_page(scratch);
out:
	return node;
}