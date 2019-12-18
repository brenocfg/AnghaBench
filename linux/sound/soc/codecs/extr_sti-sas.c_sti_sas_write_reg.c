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
struct TYPE_2__ {int /*<<< orphan*/  regmap; } ;
struct sti_sas_data {TYPE_1__ dac; } ;

/* Variables and functions */
 int regmap_write (int /*<<< orphan*/ ,unsigned int,unsigned int) ; 

__attribute__((used)) static int sti_sas_write_reg(void *context, unsigned int reg,
			     unsigned int value)
{
	struct sti_sas_data *drvdata = context;
	int status;

	status = regmap_write(drvdata->dac.regmap, reg, value);

	return status;
}