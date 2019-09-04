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
struct qoriq_tmu_data {TYPE_1__* regs; } ;
struct TYPE_2__ {int /*<<< orphan*/  tmr; int /*<<< orphan*/  tmtmir; int /*<<< orphan*/  tier; } ;

/* Variables and functions */
 int /*<<< orphan*/  TIER_DISABLE ; 
 int /*<<< orphan*/  TMR_DISABLE ; 
 int /*<<< orphan*/  TMTMIR_DEFAULT ; 
 int /*<<< orphan*/  tmu_write (struct qoriq_tmu_data*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void qoriq_tmu_init_device(struct qoriq_tmu_data *data)
{
	/* Disable interrupt, using polling instead */
	tmu_write(data, TIER_DISABLE, &data->regs->tier);

	/* Set update_interval */
	tmu_write(data, TMTMIR_DEFAULT, &data->regs->tmtmir);

	/* Disable monitoring */
	tmu_write(data, TMR_DISABLE, &data->regs->tmr);
}