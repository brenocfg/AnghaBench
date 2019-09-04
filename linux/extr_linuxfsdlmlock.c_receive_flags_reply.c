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
struct dlm_message {int m_flags; int /*<<< orphan*/  m_sbflags; } ;
struct dlm_lkb {int lkb_flags; int /*<<< orphan*/  lkb_sbflags; } ;

/* Variables and functions */
 int DLM_IFL_STUB_MS ; 

__attribute__((used)) static void receive_flags_reply(struct dlm_lkb *lkb, struct dlm_message *ms)
{
	if (ms->m_flags == DLM_IFL_STUB_MS)
		return;

	lkb->lkb_sbflags = ms->m_sbflags;
	lkb->lkb_flags = (lkb->lkb_flags & 0xFFFF0000) |
		         (ms->m_flags & 0x0000FFFF);
}