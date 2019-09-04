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
struct o2hb_bio_wait_ctxt {scalar_t__ wc_error; int /*<<< orphan*/  wc_io_complete; int /*<<< orphan*/  wc_num_reqs; } ;

/* Variables and functions */
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  init_completion (int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline void o2hb_bio_wait_init(struct o2hb_bio_wait_ctxt *wc)
{
	atomic_set(&wc->wc_num_reqs, 1);
	init_completion(&wc->wc_io_complete);
	wc->wc_error = 0;
}