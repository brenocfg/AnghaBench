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
struct TYPE_3__ {int /*<<< orphan*/  hw_rspq_ack; int /*<<< orphan*/ * hw_reqq_ack; } ;
struct TYPE_4__ {TYPE_1__ hwif; } ;
struct bfa_s {TYPE_2__ iocfc; } ;
typedef  scalar_t__ bfa_boolean_t ;

/* Variables and functions */
 int /*<<< orphan*/ * bfa_hwcb_reqq_ack_msix ; 
 int /*<<< orphan*/  bfa_hwcb_rspq_ack ; 
 int /*<<< orphan*/  bfa_hwcb_rspq_ack_msix ; 

void
bfa_hwcb_isr_mode_set(struct bfa_s *bfa, bfa_boolean_t msix)
{
	if (msix) {
		bfa->iocfc.hwif.hw_reqq_ack = bfa_hwcb_reqq_ack_msix;
		bfa->iocfc.hwif.hw_rspq_ack = bfa_hwcb_rspq_ack_msix;
	} else {
		bfa->iocfc.hwif.hw_reqq_ack = NULL;
		bfa->iocfc.hwif.hw_rspq_ack = bfa_hwcb_rspq_ack;
	}
}