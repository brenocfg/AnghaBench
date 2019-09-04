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
typedef  scalar_t__ u32 ;
struct TYPE_2__ {int /*<<< orphan*/  ioc_usage_sem_reg; int /*<<< orphan*/  ioc_usage_reg; } ;
struct bfa_ioc_s {TYPE_1__ ioc_regs; } ;

/* Variables and functions */
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  bfa_ioc_sem_get (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bfa_trc (struct bfa_ioc_s*,scalar_t__) ; 
 scalar_t__ readl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  writel (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
bfa_ioc_ct_firmware_unlock(struct bfa_ioc_s *ioc)
{
	u32 usecnt;

	/*
	 * decrement usage count
	 */
	bfa_ioc_sem_get(ioc->ioc_regs.ioc_usage_sem_reg);
	usecnt = readl(ioc->ioc_regs.ioc_usage_reg);
	WARN_ON(usecnt <= 0);

	usecnt--;
	writel(usecnt, ioc->ioc_regs.ioc_usage_reg);
	bfa_trc(ioc, usecnt);

	readl(ioc->ioc_regs.ioc_usage_sem_reg);
	writel(1, ioc->ioc_regs.ioc_usage_sem_reg);
}