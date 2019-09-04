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
struct sg_page_iter {TYPE_1__* sg; } ;
struct bio_vec {scalar_t__ bv_len; scalar_t__ bv_offset; int /*<<< orphan*/  bv_page; } ;
struct TYPE_2__ {scalar_t__ offset; } ;

/* Variables and functions */
 scalar_t__ PAGE_SIZE ; 
 int /*<<< orphan*/  sg_page_iter_page (struct sg_page_iter*) ; 

__attribute__((used)) static void nvmet_file_init_bvec(struct bio_vec *bv, struct sg_page_iter *iter)
{
	bv->bv_page = sg_page_iter_page(iter);
	bv->bv_offset = iter->sg->offset;
	bv->bv_len = PAGE_SIZE - iter->sg->offset;
}