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
struct dlm_lkb {scalar_t__ lkb_rqmode; scalar_t__ lkb_grmode; int /*<<< orphan*/  lkb_id; } ;

/* Variables and functions */
 scalar_t__ DLM_LOCK_IV ; 
 scalar_t__ DLM_LOCK_NL ; 
 int /*<<< orphan*/  log_print (char*,int /*<<< orphan*/ ,scalar_t__,scalar_t__) ; 

__attribute__((used)) static void munge_demoted(struct dlm_lkb *lkb)
{
	if (lkb->lkb_rqmode == DLM_LOCK_IV || lkb->lkb_grmode == DLM_LOCK_IV) {
		log_print("munge_demoted %x invalid modes gr %d rq %d",
			  lkb->lkb_id, lkb->lkb_grmode, lkb->lkb_rqmode);
		return;
	}

	lkb->lkb_grmode = DLM_LOCK_NL;
}