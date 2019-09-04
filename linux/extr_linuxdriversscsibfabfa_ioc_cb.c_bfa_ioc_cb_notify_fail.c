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
struct TYPE_2__ {int /*<<< orphan*/  err_set; } ;
struct bfa_ioc_s {TYPE_1__ ioc_regs; } ;

/* Variables and functions */
 int /*<<< orphan*/  readl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  writel (unsigned int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
bfa_ioc_cb_notify_fail(struct bfa_ioc_s *ioc)
{
	writel(~0U, ioc->ioc_regs.err_set);
	readl(ioc->ioc_regs.err_set);
}