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
struct reset_controller_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CMD_RESET_DEASSERT ; 
 int tegra_bpmp_reset_common (struct reset_controller_dev*,int /*<<< orphan*/ ,unsigned long) ; 

__attribute__((used)) static int tegra_bpmp_reset_deassert(struct reset_controller_dev *rstc,
				     unsigned long id)
{
	return tegra_bpmp_reset_common(rstc, CMD_RESET_DEASSERT, id);
}