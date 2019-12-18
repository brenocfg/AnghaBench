#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  h_nodeid; } ;
struct dlm_message {int /*<<< orphan*/  m_lkid; TYPE_1__ m_header; } ;
struct dlm_lkb {int /*<<< orphan*/  lkb_remid; int /*<<< orphan*/  lkb_nodeid; } ;
struct dlm_ls {struct dlm_lkb ls_stub_lkb; } ;

/* Variables and functions */

__attribute__((used)) static void setup_stub_lkb(struct dlm_ls *ls, struct dlm_message *ms)
{
	struct dlm_lkb *lkb = &ls->ls_stub_lkb;
	lkb->lkb_nodeid = ms->m_header.h_nodeid;
	lkb->lkb_remid = ms->m_lkid;
}