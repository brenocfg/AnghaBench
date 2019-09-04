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
struct timer_list {int dummy; } ;
struct llc_shdlc {int /*<<< orphan*/  sm_work; } ;

/* Variables and functions */
 struct llc_shdlc* from_timer (int /*<<< orphan*/ ,struct timer_list*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_debug (char*) ; 
 int /*<<< orphan*/  schedule_work (int /*<<< orphan*/ *) ; 
 struct llc_shdlc* shdlc ; 
 int /*<<< orphan*/  t2_timer ; 

__attribute__((used)) static void llc_shdlc_t2_timeout(struct timer_list *t)
{
	struct llc_shdlc *shdlc = from_timer(shdlc, t, t2_timer);

	pr_debug("SoftIRQ: need to retransmit\n");

	schedule_work(&shdlc->sm_work);
}