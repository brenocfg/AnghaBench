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
struct pmic_wrapper {TYPE_1__* slave; } ;
struct TYPE_2__ {int (* pwrap_read ) (struct pmic_wrapper*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ;} ;

/* Variables and functions */
 int stub1 (struct pmic_wrapper*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int pwrap_read(struct pmic_wrapper *wrp, u32 adr, u32 *rdata)
{
	return wrp->slave->pwrap_read(wrp, adr, rdata);
}