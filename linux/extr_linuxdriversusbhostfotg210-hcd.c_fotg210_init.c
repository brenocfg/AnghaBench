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
typedef  int u32 ;
struct fotg210_hcd {TYPE_1__* regs; } ;
struct TYPE_2__ {int /*<<< orphan*/  otgcsr; int /*<<< orphan*/  gmir; } ;

/* Variables and functions */
 int GMIR_INT_POLARITY ; 
 int GMIR_MDEV_INT ; 
 int GMIR_MOTG_INT ; 
 int OTGCSR_A_BUS_DROP ; 
 int OTGCSR_A_BUS_REQ ; 
 int ioread32 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  iowrite32 (int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void fotg210_init(struct fotg210_hcd *fotg210)
{
	u32 value;

	iowrite32(GMIR_MDEV_INT | GMIR_MOTG_INT | GMIR_INT_POLARITY,
			&fotg210->regs->gmir);

	value = ioread32(&fotg210->regs->otgcsr);
	value &= ~OTGCSR_A_BUS_DROP;
	value |= OTGCSR_A_BUS_REQ;
	iowrite32(value, &fotg210->regs->otgcsr);
}