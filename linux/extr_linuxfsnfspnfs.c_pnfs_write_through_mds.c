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
struct nfs_pgio_mirror {int pg_recoalesce; int /*<<< orphan*/  pg_list; } ;
struct nfs_pgio_header {TYPE_1__* completion_ops; int /*<<< orphan*/  pages; int /*<<< orphan*/  flags; } ;
struct nfs_pageio_descriptor {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* completion ) (struct nfs_pgio_header*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  NFS_IOHDR_REDO ; 
 int /*<<< orphan*/  list_splice_tail_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nfs_pageio_reset_write_mds (struct nfs_pageio_descriptor*) ; 
 struct nfs_pgio_mirror* nfs_pgio_current_mirror (struct nfs_pageio_descriptor*) ; 
 int /*<<< orphan*/  stub1 (struct nfs_pgio_header*) ; 
 int /*<<< orphan*/  test_and_set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
pnfs_write_through_mds(struct nfs_pageio_descriptor *desc,
		struct nfs_pgio_header *hdr)
{
	struct nfs_pgio_mirror *mirror = nfs_pgio_current_mirror(desc);

	if (!test_and_set_bit(NFS_IOHDR_REDO, &hdr->flags)) {
		list_splice_tail_init(&hdr->pages, &mirror->pg_list);
		nfs_pageio_reset_write_mds(desc);
		mirror->pg_recoalesce = 1;
	}
	hdr->completion_ops->completion(hdr);
}