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
struct o2hb_bio_wait_ctxt {int /*<<< orphan*/  wc_io_complete; int /*<<< orphan*/  wc_num_reqs; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 scalar_t__ atomic_dec_and_test (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  complete (int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline void o2hb_bio_wait_dec(struct o2hb_bio_wait_ctxt *wc,
				     unsigned int num)
{
	/* sadly atomic_sub_and_test() isn't available on all platforms.  The
	 * good news is that the fast path only completes one at a time */
	while(num--) {
		if (atomic_dec_and_test(&wc->wc_num_reqs)) {
			BUG_ON(num > 0);
			complete(&wc->wc_io_complete);
		}
	}
}