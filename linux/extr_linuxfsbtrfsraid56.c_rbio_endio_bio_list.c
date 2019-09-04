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
struct bio {int /*<<< orphan*/  bi_status; struct bio* bi_next; } ;
typedef  int /*<<< orphan*/  blk_status_t ;

/* Variables and functions */
 int /*<<< orphan*/  bio_endio (struct bio*) ; 

__attribute__((used)) static void rbio_endio_bio_list(struct bio *cur, blk_status_t err)
{
	struct bio *next;

	while (cur) {
		next = cur->bi_next;
		cur->bi_next = NULL;
		cur->bi_status = err;
		bio_endio(cur);
		cur = next;
	}
}