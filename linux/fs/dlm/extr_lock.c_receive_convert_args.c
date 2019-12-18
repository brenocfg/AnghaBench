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
struct dlm_message {int /*<<< orphan*/  m_lvbseq; int /*<<< orphan*/  m_rqmode; } ;
struct dlm_ls {int dummy; } ;
struct dlm_lkb {scalar_t__ lkb_status; int /*<<< orphan*/  lkb_lvbseq; int /*<<< orphan*/  lkb_rqmode; } ;

/* Variables and functions */
 scalar_t__ DLM_LKSTS_GRANTED ; 
 int EBUSY ; 
 int ENOMEM ; 
 scalar_t__ receive_lvb (struct dlm_ls*,struct dlm_lkb*,struct dlm_message*) ; 

__attribute__((used)) static int receive_convert_args(struct dlm_ls *ls, struct dlm_lkb *lkb,
				struct dlm_message *ms)
{
	if (lkb->lkb_status != DLM_LKSTS_GRANTED)
		return -EBUSY;

	if (receive_lvb(ls, lkb, ms))
		return -ENOMEM;

	lkb->lkb_rqmode = ms->m_rqmode;
	lkb->lkb_lvbseq = ms->m_lvbseq;

	return 0;
}