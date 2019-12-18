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
struct dlm_message {scalar_t__ m_type; } ;
struct dlm_lkb {int lkb_exflags; int /*<<< orphan*/  lkb_rqmode; int /*<<< orphan*/  lkb_id; } ;

/* Variables and functions */
 int DLM_LKF_ALTCW ; 
 int DLM_LKF_ALTPR ; 
 int /*<<< orphan*/  DLM_LOCK_CW ; 
 int /*<<< orphan*/  DLM_LOCK_PR ; 
 scalar_t__ DLM_MSG_GRANT ; 
 scalar_t__ DLM_MSG_REQUEST_REPLY ; 
 int /*<<< orphan*/  dlm_print_lkb (struct dlm_lkb*) ; 
 int /*<<< orphan*/  log_print (char*,int,...) ; 

__attribute__((used)) static void munge_altmode(struct dlm_lkb *lkb, struct dlm_message *ms)
{
	if (ms->m_type != DLM_MSG_REQUEST_REPLY &&
	    ms->m_type != DLM_MSG_GRANT) {
		log_print("munge_altmode %x invalid reply type %d",
			  lkb->lkb_id, ms->m_type);
		return;
	}

	if (lkb->lkb_exflags & DLM_LKF_ALTPR)
		lkb->lkb_rqmode = DLM_LOCK_PR;
	else if (lkb->lkb_exflags & DLM_LKF_ALTCW)
		lkb->lkb_rqmode = DLM_LOCK_CW;
	else {
		log_print("munge_altmode invalid exflags %x", lkb->lkb_exflags);
		dlm_print_lkb(lkb);
	}
}