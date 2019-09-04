#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int control; } ;
struct TYPE_4__ {TYPE_1__ wregs; } ;
struct sgiseeq_regs {TYPE_2__ rw; } ;
struct sgiseeq_private {int control; scalar_t__ is_edlc; } ;

/* Variables and functions */
 int SEEQ_CTRL_XCNT ; 

__attribute__((used)) static inline void tx_maybe_reset_collisions(struct sgiseeq_private *sp,
					     struct sgiseeq_regs *sregs)
{
	if (sp->is_edlc) {
		sregs->rw.wregs.control = sp->control & ~(SEEQ_CTRL_XCNT);
		sregs->rw.wregs.control = sp->control;
	}
}