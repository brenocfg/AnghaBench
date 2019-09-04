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
struct pmic_wrapper {TYPE_1__* master; } ;
struct TYPE_2__ {int type; } ;

/* Variables and functions */
 int /*<<< orphan*/  PWRAP_CSHEXT ; 
#define  PWRAP_MT8135 129 
#define  PWRAP_MT8173 128 
 int /*<<< orphan*/  pwrap_init_chip_select_ext (struct pmic_wrapper*,int /*<<< orphan*/ ,int,int,int) ; 
 int /*<<< orphan*/  pwrap_writel (struct pmic_wrapper*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int pwrap_common_init_reg_clock(struct pmic_wrapper *wrp)
{
	switch (wrp->master->type) {
	case PWRAP_MT8173:
		pwrap_init_chip_select_ext(wrp, 0, 4, 2, 2);
		break;
	case PWRAP_MT8135:
		pwrap_writel(wrp, 0x4, PWRAP_CSHEXT);
		pwrap_init_chip_select_ext(wrp, 0, 4, 0, 0);
		break;
	default:
		break;
	}

	return 0;
}