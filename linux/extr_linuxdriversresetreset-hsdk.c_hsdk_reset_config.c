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
struct hsdk_rst {scalar_t__ regs_ctl; } ;

/* Variables and functions */
 scalar_t__ CGU_SYS_RST_CTRL ; 
 int /*<<< orphan*/ * rst_map ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void hsdk_reset_config(struct hsdk_rst *rst, unsigned long id)
{
	writel(rst_map[id], rst->regs_ctl + CGU_SYS_RST_CTRL);
}