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
struct dlm_lkb {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  add_lkb (struct dlm_rsb*,struct dlm_lkb*,int) ; 
 int /*<<< orphan*/  del_lkb (struct dlm_rsb*,struct dlm_lkb*) ; 
 int /*<<< orphan*/  hold_lkb (struct dlm_lkb*) ; 
 int /*<<< orphan*/  unhold_lkb (struct dlm_lkb*) ; 

__attribute__((used)) static void move_lkb(struct dlm_rsb *r, struct dlm_lkb *lkb, int sts)
{
	hold_lkb(lkb);
	del_lkb(r, lkb);
	add_lkb(r, lkb, sts);
	unhold_lkb(lkb);
}