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
struct esp_event_ent {int /*<<< orphan*/  event; int /*<<< orphan*/  select_state; int /*<<< orphan*/  ireg; int /*<<< orphan*/  sreg2; int /*<<< orphan*/  seqreg; int /*<<< orphan*/  sreg; } ;
struct esp {int /*<<< orphan*/  event; int /*<<< orphan*/  select_state; int /*<<< orphan*/  ireg; int /*<<< orphan*/  sreg2; int /*<<< orphan*/  seqreg; int /*<<< orphan*/  sreg; } ;

/* Variables and functions */

__attribute__((used)) static void esp_log_fill_regs(struct esp *esp,
			      struct esp_event_ent *p)
{
	p->sreg = esp->sreg;
	p->seqreg = esp->seqreg;
	p->sreg2 = esp->sreg2;
	p->ireg = esp->ireg;
	p->select_state = esp->select_state;
	p->event = esp->event;
}