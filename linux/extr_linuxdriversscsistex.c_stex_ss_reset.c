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
struct st_hba {scalar_t__ mmio_base; } ;

/* Variables and functions */
 int /*<<< orphan*/  SS_H2I_INT_RESET ; 
 scalar_t__ YH2I_INT ; 
 int /*<<< orphan*/  readl (scalar_t__) ; 
 int /*<<< orphan*/  ssleep (int) ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void stex_ss_reset(struct st_hba *hba)
{
	writel(SS_H2I_INT_RESET, hba->mmio_base + YH2I_INT);
	readl(hba->mmio_base + YH2I_INT);
	ssleep(5);
}