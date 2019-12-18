#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct stm32_sai_sub_data {TYPE_3__* pdev; int /*<<< orphan*/  regmap; TYPE_2__* pdata; } ;
struct TYPE_6__ {int /*<<< orphan*/  dev; } ;
struct TYPE_4__ {int version; } ;
struct TYPE_5__ {TYPE_1__ conf; } ;

/* Variables and functions */
 int EINVAL ; 
 int SAI_XCR1_MCKDIV_MASK (int /*<<< orphan*/ ) ; 
 unsigned int SAI_XCR1_MCKDIV_MAX (int) ; 
 int SAI_XCR1_MCKDIV_SET (unsigned int) ; 
 int /*<<< orphan*/  SAI_XCR1_MCKDIV_WIDTH (int) ; 
 int /*<<< orphan*/  STM_SAI_CR1_REGX ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,...) ; 
 int regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static int stm32_sai_set_clk_div(struct stm32_sai_sub_data *sai,
				 unsigned int div)
{
	int version = sai->pdata->conf.version;
	int ret, cr1, mask;

	if (div > SAI_XCR1_MCKDIV_MAX(version)) {
		dev_err(&sai->pdev->dev, "Divider %d out of range\n", div);
		return -EINVAL;
	}

	mask = SAI_XCR1_MCKDIV_MASK(SAI_XCR1_MCKDIV_WIDTH(version));
	cr1 = SAI_XCR1_MCKDIV_SET(div);
	ret = regmap_update_bits(sai->regmap, STM_SAI_CR1_REGX, mask, cr1);
	if (ret < 0)
		dev_err(&sai->pdev->dev, "Failed to update CR1 register\n");

	return ret;
}