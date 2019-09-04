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
struct bio {int /*<<< orphan*/  bi_end_io; } ;

/* Variables and functions */
 int /*<<< orphan*/  bio_set_op_attrs (struct bio*,int,int) ; 
 int /*<<< orphan*/  guard_bio_eod (int,struct bio*) ; 
 int /*<<< orphan*/  mpage_end_io ; 
 int /*<<< orphan*/  submit_bio (struct bio*) ; 

__attribute__((used)) static struct bio *mpage_bio_submit(int op, int op_flags, struct bio *bio)
{
	bio->bi_end_io = mpage_end_io;
	bio_set_op_attrs(bio, op, op_flags);
	guard_bio_eod(op, bio);
	submit_bio(bio);
	return NULL;
}