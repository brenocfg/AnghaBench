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
struct dlm_rsb {int dummy; } ;
struct dlm_lkb {int /*<<< orphan*/  lkb_statequeue; scalar_t__ lkb_status; } ;

/* Variables and functions */
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  unhold_lkb (struct dlm_lkb*) ; 

__attribute__((used)) static void del_lkb(struct dlm_rsb *r, struct dlm_lkb *lkb)
{
	lkb->lkb_status = 0;
	list_del(&lkb->lkb_statequeue);
	unhold_lkb(lkb);
}