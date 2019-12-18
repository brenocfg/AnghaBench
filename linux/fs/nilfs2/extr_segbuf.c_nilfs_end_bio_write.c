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
struct nilfs_segment_buffer {int /*<<< orphan*/  sb_bio_event; int /*<<< orphan*/  sb_err; } ;
struct bio {scalar_t__ bi_status; struct nilfs_segment_buffer* bi_private; } ;

/* Variables and functions */
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bio_put (struct bio*) ; 
 int /*<<< orphan*/  complete (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void nilfs_end_bio_write(struct bio *bio)
{
	struct nilfs_segment_buffer *segbuf = bio->bi_private;

	if (bio->bi_status)
		atomic_inc(&segbuf->sb_err);

	bio_put(bio);
	complete(&segbuf->sb_bio_event);
}