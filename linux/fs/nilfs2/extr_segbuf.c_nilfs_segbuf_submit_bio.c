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
struct nilfs_write_info {struct bio* bio; scalar_t__ end; scalar_t__ start; int /*<<< orphan*/  rest_blocks; int /*<<< orphan*/  max_pages; int /*<<< orphan*/  nr_vecs; } ;
struct nilfs_segment_buffer {scalar_t__ sb_nbio; int /*<<< orphan*/  sb_err; int /*<<< orphan*/  sb_bio_event; TYPE_1__* sb_super; } ;
struct bio {struct nilfs_segment_buffer* bi_private; int /*<<< orphan*/  bi_end_io; } ;
struct TYPE_2__ {int /*<<< orphan*/  s_bdi; } ;

/* Variables and functions */
 int EIO ; 
 int /*<<< orphan*/  atomic_read (int /*<<< orphan*/ *) ; 
 scalar_t__ bdi_write_congested (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bio_put (struct bio*) ; 
 int /*<<< orphan*/  bio_set_op_attrs (struct bio*,int,int) ; 
 int /*<<< orphan*/  min (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nilfs_end_bio_write ; 
 int /*<<< orphan*/  submit_bio (struct bio*) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wait_for_completion (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int nilfs_segbuf_submit_bio(struct nilfs_segment_buffer *segbuf,
				   struct nilfs_write_info *wi, int mode,
				   int mode_flags)
{
	struct bio *bio = wi->bio;
	int err;

	if (segbuf->sb_nbio > 0 &&
	    bdi_write_congested(segbuf->sb_super->s_bdi)) {
		wait_for_completion(&segbuf->sb_bio_event);
		segbuf->sb_nbio--;
		if (unlikely(atomic_read(&segbuf->sb_err))) {
			bio_put(bio);
			err = -EIO;
			goto failed;
		}
	}

	bio->bi_end_io = nilfs_end_bio_write;
	bio->bi_private = segbuf;
	bio_set_op_attrs(bio, mode, mode_flags);
	submit_bio(bio);
	segbuf->sb_nbio++;

	wi->bio = NULL;
	wi->rest_blocks -= wi->end - wi->start;
	wi->nr_vecs = min(wi->max_pages, wi->rest_blocks);
	wi->start = wi->end;
	return 0;

 failed:
	wi->bio = NULL;
	return err;
}