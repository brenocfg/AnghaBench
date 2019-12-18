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
struct hd_struct {int dummy; } ;
struct bio_vec {unsigned int bv_len; unsigned int bv_offset; int /*<<< orphan*/  bv_page; } ;
struct TYPE_2__ {int bi_sector; int bi_size; } ;
struct bio {TYPE_1__ bi_iter; int /*<<< orphan*/  bi_disk; int /*<<< orphan*/  bi_partno; } ;
typedef  int sector_t ;

/* Variables and functions */
 int REQ_OP_READ ; 
 struct hd_struct* __disk_get_part (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct bio_vec* bio_last_bvec_all (struct bio*) ; 
 int get_capacity (int /*<<< orphan*/ ) ; 
 scalar_t__ likely (int) ; 
 int /*<<< orphan*/  mp_bvec_last_segment (struct bio_vec*,struct bio_vec*) ; 
 int part_nr_sects_read (struct hd_struct*) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 
 scalar_t__ unlikely (int) ; 
 int /*<<< orphan*/  zero_user (int /*<<< orphan*/ ,unsigned int,unsigned int) ; 

void guard_bio_eod(int op, struct bio *bio)
{
	sector_t maxsector;
	struct bio_vec *bvec = bio_last_bvec_all(bio);
	unsigned truncated_bytes;
	struct hd_struct *part;

	rcu_read_lock();
	part = __disk_get_part(bio->bi_disk, bio->bi_partno);
	if (part)
		maxsector = part_nr_sects_read(part);
	else
		maxsector = get_capacity(bio->bi_disk);
	rcu_read_unlock();

	if (!maxsector)
		return;

	/*
	 * If the *whole* IO is past the end of the device,
	 * let it through, and the IO layer will turn it into
	 * an EIO.
	 */
	if (unlikely(bio->bi_iter.bi_sector >= maxsector))
		return;

	maxsector -= bio->bi_iter.bi_sector;
	if (likely((bio->bi_iter.bi_size >> 9) <= maxsector))
		return;

	/* Uhhuh. We've got a bio that straddles the device size! */
	truncated_bytes = bio->bi_iter.bi_size - (maxsector << 9);

	/*
	 * The bio contains more than one segment which spans EOD, just return
	 * and let IO layer turn it into an EIO
	 */
	if (truncated_bytes > bvec->bv_len)
		return;

	/* Truncate the bio.. */
	bio->bi_iter.bi_size -= truncated_bytes;
	bvec->bv_len -= truncated_bytes;

	/* ..and clear the end of the buffer for reads */
	if (op == REQ_OP_READ) {
		struct bio_vec bv;

		mp_bvec_last_segment(bvec, &bv);
		zero_user(bv.bv_page, bv.bv_offset + bv.bv_len,
				truncated_bytes);
	}
}