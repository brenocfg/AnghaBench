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
struct bio_vec {scalar_t__ bv_page; } ;

/* Variables and functions */
 int /*<<< orphan*/  kvfree (struct bio_vec*) ; 
 int /*<<< orphan*/  put_page (scalar_t__) ; 
 int /*<<< orphan*/  set_page_dirty_lock (scalar_t__) ; 

__attribute__((used)) static void put_bvecs(struct bio_vec *bvecs, int num_bvecs, bool should_dirty)
{
	int i;

	for (i = 0; i < num_bvecs; i++) {
		if (bvecs[i].bv_page) {
			if (should_dirty)
				set_page_dirty_lock(bvecs[i].bv_page);
			put_page(bvecs[i].bv_page);
		}
	}
	kvfree(bvecs);
}