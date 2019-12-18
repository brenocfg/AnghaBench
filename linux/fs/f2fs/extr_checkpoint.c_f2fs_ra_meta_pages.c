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
struct page {int dummy; } ;
struct f2fs_sb_info {int dummy; } ;
struct f2fs_io_info {int op_flags; int in_list; int is_por; int new_blkaddr; struct page* page; int /*<<< orphan*/ * encrypted_page; int /*<<< orphan*/  op; int /*<<< orphan*/  type; struct f2fs_sb_info* sbi; } ;
struct blk_plug {int dummy; } ;
typedef  int block_t ;
struct TYPE_2__ {int /*<<< orphan*/  max_nid; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG () ; 
 int /*<<< orphan*/  META ; 
#define  META_CP 132 
 int /*<<< orphan*/  META_MAPPING (struct f2fs_sb_info*) ; 
#define  META_NAT 131 
#define  META_POR 130 
#define  META_SIT 129 
#define  META_SSA 128 
 int NAT_BLOCK_OFFSET (int /*<<< orphan*/ ) ; 
 int NAT_ENTRY_PER_BLOCK ; 
 TYPE_1__* NM_I (struct f2fs_sb_info*) ; 
 scalar_t__ PageUptodate (struct page*) ; 
 int REQ_META ; 
 int /*<<< orphan*/  REQ_OP_READ ; 
 int REQ_PRIO ; 
 int REQ_RAHEAD ; 
 int SIT_ENTRY_PER_BLOCK ; 
 int /*<<< orphan*/  blk_finish_plug (struct blk_plug*) ; 
 int /*<<< orphan*/  blk_start_plug (struct blk_plug*) ; 
 int current_nat_addr (struct f2fs_sb_info*,int) ; 
 int current_sit_addr (struct f2fs_sb_info*,int) ; 
 struct page* f2fs_grab_cache_page (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  f2fs_is_valid_blkaddr (struct f2fs_sb_info*,int,int) ; 
 int /*<<< orphan*/  f2fs_put_page (struct page*,int) ; 
 int /*<<< orphan*/  f2fs_submit_page_bio (struct f2fs_io_info*) ; 
 scalar_t__ unlikely (int) ; 

int f2fs_ra_meta_pages(struct f2fs_sb_info *sbi, block_t start, int nrpages,
							int type, bool sync)
{
	struct page *page;
	block_t blkno = start;
	struct f2fs_io_info fio = {
		.sbi = sbi,
		.type = META,
		.op = REQ_OP_READ,
		.op_flags = sync ? (REQ_META | REQ_PRIO) : REQ_RAHEAD,
		.encrypted_page = NULL,
		.in_list = false,
		.is_por = (type == META_POR),
	};
	struct blk_plug plug;

	if (unlikely(type == META_POR))
		fio.op_flags &= ~REQ_META;

	blk_start_plug(&plug);
	for (; nrpages-- > 0; blkno++) {

		if (!f2fs_is_valid_blkaddr(sbi, blkno, type))
			goto out;

		switch (type) {
		case META_NAT:
			if (unlikely(blkno >=
					NAT_BLOCK_OFFSET(NM_I(sbi)->max_nid)))
				blkno = 0;
			/* get nat block addr */
			fio.new_blkaddr = current_nat_addr(sbi,
					blkno * NAT_ENTRY_PER_BLOCK);
			break;
		case META_SIT:
			/* get sit block addr */
			fio.new_blkaddr = current_sit_addr(sbi,
					blkno * SIT_ENTRY_PER_BLOCK);
			break;
		case META_SSA:
		case META_CP:
		case META_POR:
			fio.new_blkaddr = blkno;
			break;
		default:
			BUG();
		}

		page = f2fs_grab_cache_page(META_MAPPING(sbi),
						fio.new_blkaddr, false);
		if (!page)
			continue;
		if (PageUptodate(page)) {
			f2fs_put_page(page, 1);
			continue;
		}

		fio.page = page;
		f2fs_submit_page_bio(&fio);
		f2fs_put_page(page, 0);
	}
out:
	blk_finish_plug(&plug);
	return blkno - start;
}