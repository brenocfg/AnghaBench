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
struct pic32_dmt {scalar_t__ regs; } ;

/* Variables and functions */
 scalar_t__ DMTCON_REG ; 
 int /*<<< orphan*/  DMT_ON ; 
 int /*<<< orphan*/  PIC32_SET (scalar_t__) ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void dmt_enable(struct pic32_dmt *dmt)
{
	writel(DMT_ON, PIC32_SET(dmt->regs + DMTCON_REG));
}