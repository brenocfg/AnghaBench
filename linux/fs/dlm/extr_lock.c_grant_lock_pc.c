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
struct dlm_message {int dummy; } ;
struct dlm_lkb {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  _grant_lock (struct dlm_rsb*,struct dlm_lkb*) ; 
 int /*<<< orphan*/  set_lvb_lock_pc (struct dlm_rsb*,struct dlm_lkb*,struct dlm_message*) ; 

__attribute__((used)) static void grant_lock_pc(struct dlm_rsb *r, struct dlm_lkb *lkb,
			  struct dlm_message *ms)
{
	set_lvb_lock_pc(r, lkb, ms);
	_grant_lock(r, lkb);
}