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
struct stm32_sai_sub_data {TYPE_3__* pdev; TYPE_2__* pdata; } ;
struct TYPE_6__ {int /*<<< orphan*/  dev; } ;
struct TYPE_4__ {int version; } ;
struct TYPE_5__ {TYPE_1__ conf; } ;

/* Variables and functions */
 int DIV_ROUND_CLOSEST (unsigned long,unsigned long) ; 
 int EINVAL ; 
 int SAI_XCR1_MCKDIV_MAX (int) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,unsigned long,...) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int) ; 

__attribute__((used)) static int stm32_sai_get_clk_div(struct stm32_sai_sub_data *sai,
				 unsigned long input_rate,
				 unsigned long output_rate)
{
	int version = sai->pdata->conf.version;
	int div;

	div = DIV_ROUND_CLOSEST(input_rate, output_rate);
	if (div > SAI_XCR1_MCKDIV_MAX(version)) {
		dev_err(&sai->pdev->dev, "Divider %d out of range\n", div);
		return -EINVAL;
	}
	dev_dbg(&sai->pdev->dev, "SAI divider %d\n", div);

	if (input_rate % div)
		dev_dbg(&sai->pdev->dev,
			"Rate not accurate. requested (%ld), actual (%ld)\n",
			output_rate, input_rate / div);

	return div;
}