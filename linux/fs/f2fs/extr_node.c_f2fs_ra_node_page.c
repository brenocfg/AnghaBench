#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct page {int dummy; } ;
struct f2fs_sb_info {int dummy; } ;
typedef  int /*<<< orphan*/  nid_t ;
struct TYPE_3__ {int /*<<< orphan*/  i_pages; } ;

/* Variables and functions */
 TYPE_1__* NODE_MAPPING (struct f2fs_sb_info*) ; 
 int /*<<< orphan*/  REQ_RAHEAD ; 
 scalar_t__ f2fs_check_nid_range (struct f2fs_sb_info*,int /*<<< orphan*/ ) ; 
 struct page* f2fs_grab_cache_page (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  f2fs_put_page (struct page*,int) ; 
 int read_node_page (struct page*,int /*<<< orphan*/ ) ; 
 struct page* xa_load (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void f2fs_ra_node_page(struct f2fs_sb_info *sbi, nid_t nid)
{
	struct page *apage;
	int err;

	if (!nid)
		return;
	if (f2fs_check_nid_range(sbi, nid))
		return;

	apage = xa_load(&NODE_MAPPING(sbi)->i_pages, nid);
	if (apage)
		return;

	apage = f2fs_grab_cache_page(NODE_MAPPING(sbi), nid, false);
	if (!apage)
		return;

	err = read_node_page(apage, REQ_RAHEAD);
	f2fs_put_page(apage, err ? 1 : 0);
}