#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int u64 ;
struct request_queue {int dummy; } ;
struct page {int dummy; } ;
struct ore_striping_info {unsigned int dev; int obj_offset; } ;
struct ore_per_dev_state {int length; int offset; unsigned int dev; TYPE_3__* bio; } ;
struct ore_io_state {int numdevs; int /*<<< orphan*/  oc; TYPE_2__* sp2d; struct ore_per_dev_state* per_dev; TYPE_1__* layout; struct ore_io_state* ios_read_4_write; } ;
struct TYPE_7__ {int /*<<< orphan*/  bi_vcnt; } ;
struct TYPE_6__ {int /*<<< orphan*/  pages_in_unit; } ;
struct TYPE_5__ {unsigned int group_width; unsigned int mirrors_p1; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  ORE_DBGMSG (char*,int /*<<< orphan*/ ) ; 
 int PAGE_SIZE ; 
 int _alloc_read_4_write (struct ore_io_state*) ; 
 int /*<<< orphan*/  _ore_add_sg_seg (struct ore_per_dev_state*,int,int) ; 
 unsigned int bio_add_pc_page (struct request_queue*,TYPE_3__*,struct page*,unsigned int,int) ; 
 TYPE_3__* bio_kmalloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ore_comp_dev (int /*<<< orphan*/ ,unsigned int) ; 
 struct request_queue* osd_request_queue (int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int _add_to_r4w(struct ore_io_state *ios, struct ore_striping_info *si,
		       struct page *page, unsigned pg_len)
{
	struct request_queue *q;
	struct ore_per_dev_state *per_dev;
	struct ore_io_state *read_ios;
	unsigned first_dev = si->dev - (si->dev %
			  (ios->layout->group_width * ios->layout->mirrors_p1));
	unsigned comp = si->dev - first_dev;
	unsigned added_len;

	if (!ios->ios_read_4_write) {
		int ret = _alloc_read_4_write(ios);

		if (unlikely(ret))
			return ret;
	}

	read_ios = ios->ios_read_4_write;
	read_ios->numdevs = ios->layout->group_width * ios->layout->mirrors_p1;

	per_dev = &read_ios->per_dev[comp];
	if (!per_dev->length) {
		per_dev->bio = bio_kmalloc(GFP_KERNEL,
					   ios->sp2d->pages_in_unit);
		if (unlikely(!per_dev->bio)) {
			ORE_DBGMSG("Failed to allocate BIO size=%u\n",
				     ios->sp2d->pages_in_unit);
			return -ENOMEM;
		}
		per_dev->offset = si->obj_offset;
		per_dev->dev = si->dev;
	} else if (si->obj_offset != (per_dev->offset + per_dev->length)) {
		u64 gap = si->obj_offset - (per_dev->offset + per_dev->length);

		_ore_add_sg_seg(per_dev, gap, true);
	}
	q = osd_request_queue(ore_comp_dev(read_ios->oc, per_dev->dev));
	added_len = bio_add_pc_page(q, per_dev->bio, page, pg_len,
				    si->obj_offset % PAGE_SIZE);
	if (unlikely(added_len != pg_len)) {
		ORE_DBGMSG("Failed to bio_add_pc_page bi_vcnt=%d\n",
			      per_dev->bio->bi_vcnt);
		return -ENOMEM;
	}

	per_dev->length += pg_len;
	return 0;
}