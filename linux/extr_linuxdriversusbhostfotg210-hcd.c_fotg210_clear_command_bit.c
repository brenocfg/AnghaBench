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
typedef  int /*<<< orphan*/  u32 ;
struct fotg210_hcd {TYPE_1__* regs; int /*<<< orphan*/  command; } ;
struct TYPE_2__ {int /*<<< orphan*/  command; } ;

/* Variables and functions */
 int /*<<< orphan*/  fotg210_readl (struct fotg210_hcd*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fotg210_writel (struct fotg210_hcd*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void fotg210_clear_command_bit(struct fotg210_hcd *fotg210, u32 bit)
{
	fotg210->command &= ~bit;
	fotg210_writel(fotg210, fotg210->command, &fotg210->regs->command);

	/* unblock posted write */
	fotg210_readl(fotg210, &fotg210->regs->command);
}