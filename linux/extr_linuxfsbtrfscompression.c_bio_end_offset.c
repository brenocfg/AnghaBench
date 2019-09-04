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
typedef  scalar_t__ u64 ;
struct bio_vec {scalar_t__ bv_offset; scalar_t__ bv_len; int /*<<< orphan*/  bv_page; } ;
struct bio {int dummy; } ;

/* Variables and functions */
 struct bio_vec* bio_last_bvec_all (struct bio*) ; 
 scalar_t__ page_offset (int /*<<< orphan*/ ) ; 

__attribute__((used)) static u64 bio_end_offset(struct bio *bio)
{
	struct bio_vec *last = bio_last_bvec_all(bio);

	return page_offset(last->bv_page) + last->bv_len + last->bv_offset;
}