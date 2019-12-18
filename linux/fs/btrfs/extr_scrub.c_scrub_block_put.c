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
struct scrub_block {int page_count; int /*<<< orphan*/ * pagev; scalar_t__ sparity; int /*<<< orphan*/  refs; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct scrub_block*) ; 
 scalar_t__ refcount_dec_and_test (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  scrub_page_put (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  scrub_parity_put (scalar_t__) ; 

__attribute__((used)) static void scrub_block_put(struct scrub_block *sblock)
{
	if (refcount_dec_and_test(&sblock->refs)) {
		int i;

		if (sblock->sparity)
			scrub_parity_put(sblock->sparity);

		for (i = 0; i < sblock->page_count; i++)
			scrub_page_put(sblock->pagev[i]);
		kfree(sblock);
	}
}