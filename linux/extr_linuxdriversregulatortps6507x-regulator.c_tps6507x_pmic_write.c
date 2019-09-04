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
typedef  int /*<<< orphan*/  u8 ;
struct tps6507x_pmic {TYPE_1__* mfd; } ;
struct TYPE_2__ {int (* write_dev ) (TYPE_1__*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ;} ;

/* Variables and functions */
 int stub1 (TYPE_1__*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline int tps6507x_pmic_write(struct tps6507x_pmic *tps, u8 reg, u8 val)
{
	return tps->mfd->write_dev(tps->mfd, reg, 1, &val);
}