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
struct dlm_message {int m_flags; int /*<<< orphan*/  m_sbflags; int /*<<< orphan*/  m_exflags; } ;
struct dlm_lkb {int lkb_flags; int /*<<< orphan*/  lkb_sbflags; int /*<<< orphan*/  lkb_exflags; } ;

/* Variables and functions */

__attribute__((used)) static void receive_flags(struct dlm_lkb *lkb, struct dlm_message *ms)
{
	lkb->lkb_exflags = ms->m_exflags;
	lkb->lkb_sbflags = ms->m_sbflags;
	lkb->lkb_flags = (lkb->lkb_flags & 0xFFFF0000) |
		         (ms->m_flags & 0x0000FFFF);
}