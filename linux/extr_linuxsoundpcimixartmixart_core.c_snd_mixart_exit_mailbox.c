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
struct mixart_mgr {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MIXART_HOST_ALL_INTERRUPT_MASKED ; 
 int /*<<< orphan*/  MIXART_PCI_OMIMR_OFFSET ; 
 int /*<<< orphan*/  MIXART_REG (struct mixart_mgr*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  writel_le (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void snd_mixart_exit_mailbox(struct mixart_mgr *mgr)
{
	/* no more interrupts on outbound messagebox */
	writel_le( MIXART_HOST_ALL_INTERRUPT_MASKED, MIXART_REG( mgr, MIXART_PCI_OMIMR_OFFSET));
	return;
}