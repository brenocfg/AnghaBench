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
typedef  int /*<<< orphan*/  u32 ;
struct vscsibk_pend {int n_grants; struct vscsibk_info* info; } ;
struct vscsibk_info {int /*<<< orphan*/  domid; } ;
struct scsiif_request_segment {int /*<<< orphan*/  gref; } ;
struct page {int dummy; } ;
struct gnttab_map_grant_ref {int dummy; } ;
typedef  int /*<<< orphan*/  grant_handle_t ;

/* Variables and functions */
 int ENOMEM ; 
 int VSCSI_GRANT_BATCH ; 
 scalar_t__ get_free_page (struct page**) ; 
 int /*<<< orphan*/  gnttab_set_map_op (struct gnttab_map_grant_ref*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_err (char*) ; 
 int /*<<< orphan*/  put_free_pages (struct page**,int) ; 
 int scsiback_gnttab_data_map_batch (struct gnttab_map_grant_ref*,struct page**,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  vaddr_page (struct page*) ; 

__attribute__((used)) static int scsiback_gnttab_data_map_list(struct vscsibk_pend *pending_req,
			struct scsiif_request_segment *seg, struct page **pg,
			grant_handle_t *grant, int cnt, u32 flags)
{
	int mapcount = 0, i, err = 0;
	struct gnttab_map_grant_ref map[VSCSI_GRANT_BATCH];
	struct vscsibk_info *info = pending_req->info;

	for (i = 0; i < cnt; i++) {
		if (get_free_page(pg + mapcount)) {
			put_free_pages(pg, mapcount);
			pr_err("no grant page\n");
			return -ENOMEM;
		}
		gnttab_set_map_op(&map[mapcount], vaddr_page(pg[mapcount]),
				  flags, seg[i].gref, info->domid);
		mapcount++;
		if (mapcount < VSCSI_GRANT_BATCH)
			continue;
		err = scsiback_gnttab_data_map_batch(map, pg, grant, mapcount);
		pg += mapcount;
		grant += mapcount;
		pending_req->n_grants += mapcount;
		if (err)
			return err;
		mapcount = 0;
	}
	err = scsiback_gnttab_data_map_batch(map, pg, grant, mapcount);
	pending_req->n_grants += mapcount;
	return err;
}