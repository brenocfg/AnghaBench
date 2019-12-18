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
struct o2hb_bio_wait_ctxt {int /*<<< orphan*/  wc_io_complete; } ;

/* Variables and functions */
 int /*<<< orphan*/  o2hb_bio_wait_dec (struct o2hb_bio_wait_ctxt*,int) ; 
 int /*<<< orphan*/  wait_for_completion (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void o2hb_wait_on_io(struct o2hb_bio_wait_ctxt *wc)
{
	o2hb_bio_wait_dec(wc, 1);
	wait_for_completion(&wc->wc_io_complete);
}